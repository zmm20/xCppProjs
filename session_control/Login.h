#pragma once

#include <string>


struct SessionData
{
	static const std::string uid_;
	static const std::string pwd_;
	static const std::string loginin_;
	static const std::string nick_;
	static const std::string username_;
	static const std::string password_;
};

//Session keys
const std::string SessionData::uid_ = "user";
const std::string SessionData::pwd_ = "password";
const std::string SessionData::loginin_ = "loginin";
const std::string SessionData::nick_ = "nick";
//�û���������
const std::string SessionData::username_ = "zmm";
const std::string SessionData::password_ = "e10adc3949ba59abbe56e057f20f883e";	//123456

struct LoginControl
{
	void before(cinatra::Request& /* req */, cinatra::Response& /* res */,cinatra::ContextContainer& /*ctx*/)
	{
		
		/*if (req.session().exists(SessionData::loginin_)
			&& req.session().get<bool>(SessionData::loginin_) == true)
			{
				res.cookies().new_cookie()
					.add("uid", req.session().get<std::string>(SessionData::uid_))
					.max_age(10 * 60) //10���ӵĵ�½��Ч��
					.new_cookie()
					.add("flag", "1")
					.max_age(10 * 60);
			}*/
	}

	void after(cinatra::Request& /* req */, cinatra::Response& /* res */, cinatra::ContextContainer& /*ctx*/)
	{

	}

private:

};
