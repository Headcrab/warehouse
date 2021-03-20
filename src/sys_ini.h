/*-----------------------------------------------------------------------------
 Unit Name: sys_ini
 Author:	Alex Novikov
 Date:		16.02.04
 Purpose: 	Работа с ini файлами.
 History:
 16.03.21	v0.2 - переделан на работу с std::string
-----------------------------------------------------------------------------*/

//---------------------------------------------------------------------------
#ifndef sys_iniH
#define sys_iniH
//---------------------------------------------------------------------------

#include <algorithm>
#include <sstream>
#include <string>
#include <vector>

//---------------------------------------------------------------------------

namespace app {

using std::string;
using std::transform;
using std::vector;

inline string to_lower(string in)
{
	char* locale = setlocale(LC_ALL, NULL);
	setlocale(LC_ALL, "rus");
	transform(in.begin(), in.end(), in.begin(), tolower);
	setlocale(LC_ALL, locale);
	return in;
}

inline int to_int(string const& s)
{
	return atoi(s.c_str());
}

inline string to_string(int i)
{
	std::stringstream out;
	out << i;
	return out.str();
}

inline double to_double(string const& s)
{
	return atof(s.c_str());
}

inline string to_string(double i)
{
	std::stringstream out;
	out << i;
	return out.str();
}

inline bool to_bool(string const& s)
{
	return s != "0";
}

inline string to_string(bool b)
{
	return b ? "true" : "false";
}

class ini {
public:
	ini(string n = "")
	{
		filename_ = n;
		if (filename_ == "")
			filename_ = get_app_name() + ".ini";
		//		if (ExtractFilePath(filename_) == "")
		//			filename_ = ExtractFilePath(Application->ExeName) + "\\" + filename_;
		get_sections();
		all_lower_ = false;
		//		if(filename_=="") filename_ = Application->ExeName + ".ini";
	}

	void all_lower()
	{
		all_lower_ = true;
	}

	// - sections iterator -

	typedef vector<string>::iterator section_iterator;
	vector<string>::iterator begin_section()
	{
		return sections_.begin();
	};
	vector<string>::iterator end_section()
	{
		return sections_.end();
	}

	void erase_section(string sect)
	{
		WritePrivateProfileSection(sect.c_str(), 0, filename_.c_str());
	}

	// - keys iterator -

	typedef vector<string>::iterator key_iterator;
	vector<string>::iterator begin_key(string s)
	{
		get_keys(s);
		return keys_.begin();
	};
	vector<string>::iterator end_key()
	{
		return keys_.end();
	}

	// - get -

	string get(string group, string key, string def = "")
	{
		const int bufsize = 60000;
		static char buf[bufsize];
		GetPrivateProfileString(group.c_str(), key.c_str(), def.c_str(), buf, bufsize, filename_.c_str());
		if (all_lower_)
			return to_lower(string(buf));
		else
			return string(buf);
	}

	bool get_bool(string group, string key, bool def = false)
	{
		bool c = def;
		try {
			c = to_bool(get(group, key, to_string(def)));
		} catch (...) {
		}
		return c;
	}

	int get_int(string group, string key, int def = -1)
	{
		return to_int(get(group, key, to_string(def)));
	}

	double get_float(string group, string key, double def = -1.0)
	{
		return to_double(get(group, key, to_string(def)));
	}
	/*
	TDateTime get_date(string group, string key)//,TDateTime def = Date())
	{
		//		return StrToDateTime(get(group,key,DateTimeToStr(def)));
		string d = get(group, key);
		if (d == "")
			return 0;
		return StrToDateTime(d);
	}
*/
	// - set -

	void set(string group, string key, string val)
	{
		if (all_lower_)
			WritePrivateProfileString(group.c_str(), key.c_str(), to_lower(val).c_str(), filename_.c_str());
		else
			WritePrivateProfileString(group.c_str(), key.c_str(), val.c_str(), filename_.c_str());
	}

	void set_bool(string group, string key, bool val)
	{
		set(group, key, to_string(val));
	}

	void set_int(string group, string key, int val)
	{
		set(group, key, to_string(val));
	}

	void set_float(string group, string key, double val)
	{
		set(group, key, to_string(val));
	}
	/*
	void set_date(string group, string key, TDateTime val)
	{
		set(group, key, DateTimeToStr(val));
	}
*/
private:
	string filename_;
	vector<string> sections_;
	vector<string> keys_;
	bool all_lower_;

	void get_keys(string sect)
	{
		const int bufsize = 4096;
		static char buf[bufsize];
		int cnt = GetPrivateProfileSection(sect.c_str(), buf, bufsize, filename_.c_str());
		keys_.clear();
		if (cnt == 0)
			return;
		string b = "";
		for (int i = 0; i != cnt; i++) {
			if (buf[i] == '\0') {
				keys_.push_back(b.substr(0, b.find("=", 0)));
				b = "";
				continue;
			}
			b += buf[i];
		}
	}

	void get_sections()
	{
		const int bufsize = 4096;
		static char buf[bufsize];
		int cnt = GetPrivateProfileSectionNames(buf, bufsize, filename_.c_str());
		sections_.clear();
		if (cnt == 0)
			return;
		string b = "";
		for (int i = 0; i != cnt; i++) {
			if (buf[i] == '\0') {
				sections_.push_back(b);
				b = "";
				continue;
			}
			b += buf[i];
		}
	}

	string get_app_name()
	{
		char buf[MAX_PATH];
		GetModuleFileNameA(NULL, buf, MAX_PATH);
		string s(buf);
		string fn = s.substr(0, s.find(".", 0));
		return fn;
	}
};

class app_ini {
public:
	static ini& get(string g = "")
	{
		static ini statiini(g.c_str());
		return statiini;
	}

	static ini& set(string g = "")
	{
		return get(g);
	}
	/*
		ini& operator ()()
		{
			return get("");
		}
	*/
private:
	app_ini();
	~app_ini();
};

}; //namespace app

//---------------------------------------------------------------------------
#endif
