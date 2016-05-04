#pragma once
#include <string>
#include <mutex>

class UserData
{
private:
	std::string message;
	bool sent;
	std::mutex mtx;

public:
	UserData()
	{
		sent = true;
	}

	void SetMessage(std::string _message)
	{
		mtx.lock();
		message = _message;
		sent = false;
		mtx.unlock();
	}

	bool Get_Message(std::string& _message)
	{
		bool ret;
		mtx.lock();
		if (sent)
		{
			ret = false;
		}
		else
		{
			_message = message;
			sent = true;
			ret = true;
		}
		mtx.unlock();
		return ret;
	}
	~UserData() {}
};
