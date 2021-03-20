CREATE TABLE master.dbo.Clients
(
  ID int IDENTITY(0,1) NOT NULL,
  Name varchar(100) COLLATE Cyrillic_General_CI_AS NOT NULL
) GO;

CREATE TABLE master.dbo.Product
(
  ID int IDENTITY(1,1) NOT NULL,
  Name varchar(100) COLLATE Cyrillic_General_CI_AS NOT NULL
) GO;

CREATE TABLE master.dbo.Provider
(
  ID int IDENTITY(1,1) NOT NULL,
  Name varchar(100) COLLATE Cyrillic_General_CI_AS NOT NULL
) GO;

CREATE TABLE master.dbo.Store
(
  ID int IDENTITY(0,1) NOT NULL,
  productID int NOT NULL,
  Cnt float NOT NULL,
  StoreID int NOT NULL
) GO;

CREATE TABLE master.dbo.Stores
(
  ID int IDENTITY(1,1) NOT NULL,
  Name varchar(100) COLLATE Cyrillic_General_CI_AS NOT NULL
) GO;

CREATE TABLE master.dbo.prod_in
(
  ID int IDENTITY(0,1) NOT NULL,
  providerID int NOT NULL,
  productID int NOT NULL,
  Cnt float NOT NULL,
  StoreID int NOT NULL
) GO;


CREATE TABLE master.dbo.prod_out
(
  ID int IDENTITY(0,1) NOT NULL,
  clientsID int NOT NULL,
  productID int NOT NULL,
  Cnt float NOT NULL,
  storeID int NOT NULL
) GO;

create view prod_in_state
as
  select a.Name 'Provider', p.Name 'Product', pri.Cnt 'Count', s2.Name 'Store'
  from prod_in pri
    left join Stores s2 on s2.id=pri.StoreID
    left join Product p on p.id=pri.productID
    left join Provider a on a.id = pri.providerID;
GO

create view prod_out_state
as
  select a.Name 'Client', p.Name 'Product', pro.Cnt 'Count', s2.Name 'Store'
  from prod_out pro
    left join Stores s2 on s2.id=pro.StoreID
    left join Product p on p.id=pro.productID
    left join Clients a on a.id = pro.clientsID;
GO

create view spt_values
as
  select name collate database_default as name,
    number,
    type collate database_default as type,
    low, high, status
  from sys.spt_values;
GO

create view store_state
as
  select s2.Name Store, p.Name Product, s.Cnt
  from Store s
    left join Stores s2 on s2.id=s.StoreID
    left join Product p on p.id=s.productID;
GO

CREATE TRIGGER prod_in_insert ON prod_in AFTER INSERT AS
begin
  declare @ins_productID as int, @ins_cnt as int, @ins_storeID as int, @st_id as int
  select @ins_productID=productID , @ins_cnt=cnt, @ins_storeID=storeID
  from inserted
  select distinct @st_id=count(st.id)
  from store st
  where st.productID=@ins_productID and st.StoreID=@ins_StoreID
  if (@st_id=0) 
	begin
    insert into Store
      (productID, Cnt, StoreID)
    values
      (@ins_productID, @ins_cnt , @ins_StoreID)
  end
else 
	begin
    update store set store.Cnt = store.Cnt+@ins_cnt where store.productID=@ins_productID and store.StoreID=@ins_StoreID
  end
end
GO

CREATE TRIGGER prod_out_insert ON prod_out after INSERT AS
begin
  declare @ins_productID as int, @ins_cnt as int, @ins_storeID as int, @st_cnt as int
  select @ins_productID=productID , @ins_cnt=cnt, @ins_storeID=storeID
  from inserted
  select distinct @st_cnt=st.cnt
  from store st
  where st.productID=@ins_productID and st.StoreID=@ins_StoreID
  if (@st_cnt-@ins_cnt<0) 
begin
    rollback transaction
    return
  end
else 
begin
    update store set store.Cnt = store.Cnt-@ins_cnt where store.productID=@ins_productID and store.StoreID=@ins_StoreID
    return
  end
end
GO



