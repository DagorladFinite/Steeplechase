#pragma once
#include <string>
#include <TCPSocket.h>

class ClientProxy
{
private:
	std::string nick;
	int score;
	std::shared_ptr<TCPSocket> tcpSocket;

public:
	ClientProxy();
	void SetSocket(std::shared_ptr<TCPSocket> _tcpSocket);
	std::string GetNick();
	void SetNick(std::string _nick);
	int GetScore();
	void SetScore(int _score);
	void AddScore();
	int Send(std::string _msg);
	int Receive(std::string& _msg);
	bool operator==(ClientProxy& _clientProxy);
	~ClientProxy();
};

