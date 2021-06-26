#include <string>
#include <vector>
#include <cstring>
#ifndef WIN32
#	include <netinet/in.h>
#endif
#include "SAMPRakNet.hpp"

char 
	SAMPRakNet::
	sendBuffer[4092];

uint8_t
	SAMPRakNet::
	buffer_[MAXIMUM_MTU_SIZE];

uint32_t
	SAMPRakNet::
	token_;

uint16_t
	SAMPRakNet::
	maxPlayers;

std::unordered_map<std::string, int>
	SAMPRakNet::
	players;

std::string
	SAMPRakNet::
	serverName;

std::string
	SAMPRakNet::
	gameModeName;

std::unordered_map<std::string, std::string>
	SAMPRakNet::
	rules;

uint16_t
	SAMPRakNet::
	portNumber = 7777;

uint16_t
	SAMPRakNet::
	GetPort()
{
	return portNumber;
}

void
	SAMPRakNet::
	SetPort(uint16_t value)
{
	portNumber = value;
}

uint16_t
	SAMPRakNet::
	GetPlayerCount()
{
	return static_cast<uint16_t>(players.size());
}

uint16_t
	SAMPRakNet::
	GetMaxPlayers()
{
	return maxPlayers;
}

void
	SAMPRakNet::
	SetMaxPlayers(uint16_t value)
{
	maxPlayers = value;
}

std::unordered_map<std::string, int> &
	SAMPRakNet::
	GetPlayers()
{
	return players;
}

void
	SAMPRakNet::
	AddPlayerToPool(const std::string& playerName, int score)
{
	auto _player = players.find(playerName);
	if (_player == players.end())
	{
		players.insert({ playerName, score });
	}
}

void
	SAMPRakNet::
	RemovePlayerFromPool(const std::string& playerName)
{
	auto _player = players.find(playerName);
	if (_player != players.end())
	{
		players.erase(playerName);
	}
}

std::string &
	SAMPRakNet::
	GetServerName()
{
	return serverName;
}

void
	SAMPRakNet::
	SetServerName(const std::string & value)
{
	serverName = value;
}

std::string &
	SAMPRakNet::
	GetGameModeName()
{
	return gameModeName;
}

void
	SAMPRakNet::
	SetGameModeName(const std::string& value)
{
	gameModeName = value;
}

std::unordered_map<std::string, std::string> &
	SAMPRakNet::
	GetRules()
{
	return rules;
}

template<typename... Args>
void
	SAMPRakNet::
	SetRuleValue(const Args &... args)
{
	std::vector<std::string> ruleData = { args... };
	int ruleCount = ruleData.size();
	if (ruleCount % 2)
	{
		ruleCount--;
	}

	for (int index = 0; index < ruleCount; index += 2)
	{
		const std::string 
			& ruleName = ruleData[index];
		const std::string
			& ruleValue = ruleData[index + 1];
		rules[ruleName] = ruleValue;
	}
}

void
	SAMPRakNet::
	RemoveRule(const std::string & ruleName)
{
	auto _rule = rules.find(ruleName);
	if (_rule != rules.end())
	{
		rules.erase(ruleName);
	}
}

template<typename T>
void 
	SAMPRakNet::
	WriteToSendBuffer(unsigned int & offset, T value, unsigned int size)
{
	*reinterpret_cast<T*>(&sendBuffer[offset]) = value;
	offset += size;
}

void 
	SAMPRakNet::
	WriteToSendBuffer(char const * src, unsigned int & offset, unsigned int size)
{
	strncpy(&sendBuffer[offset], src, size);
	offset += size;
}

uint8_t *
	SAMPRakNet::
	Decrypt(uint8_t const * src, int len)
{
	static const uint8_t
		key[256] = {
			0xB4, 0x62, 0x07, 0xE5, 0x9D, 0xAF, 0x63, 0xDD, 0xE3, 0xD0, 0xCC, 0xFE, 0xDC, 0xDB, 0x6B, 0x2E,
			0x6A, 0x40, 0xAB, 0x47, 0xC9, 0xD1, 0x53, 0xD5, 0x20, 0x91, 0xA5, 0x0E, 0x4A, 0xDF, 0x18, 0x89,
			0xFD, 0x6F, 0x25, 0x12, 0xB7, 0x13, 0x77, 0x00, 0x65, 0x36, 0x6D, 0x49, 0xEC, 0x57, 0x2A, 0xA9,
			0x11, 0x5F, 0xFA, 0x78, 0x95, 0xA4, 0xBD, 0x1E, 0xD9, 0x79, 0x44, 0xCD, 0xDE, 0x81, 0xEB, 0x09,
			0x3E, 0xF6, 0xEE, 0xDA, 0x7F, 0xA3, 0x1A, 0xA7, 0x2D, 0xA6, 0xAD, 0xC1, 0x46, 0x93, 0xD2, 0x1B,
			0x9C, 0xAA, 0xD7, 0x4E, 0x4B, 0x4D, 0x4C, 0xF3, 0xB8, 0x34, 0xC0, 0xCA, 0x88, 0xF4, 0x94, 0xCB,
			0x04, 0x39, 0x30, 0x82, 0xD6, 0x73, 0xB0, 0xBF, 0x22, 0x01, 0x41, 0x6E, 0x48, 0x2C, 0xA8, 0x75,
			0xB1, 0x0A, 0xAE, 0x9F, 0x27, 0x80, 0x10, 0xCE, 0xF0, 0x29, 0x28, 0x85, 0x0D, 0x05, 0xF7, 0x35,
			0xBB, 0xBC, 0x15, 0x06, 0xF5, 0x60, 0x71, 0x03, 0x1F, 0xEA, 0x5A, 0x33, 0x92, 0x8D, 0xE7, 0x90,
			0x5B, 0xE9, 0xCF, 0x9E, 0xD3, 0x5D, 0xED, 0x31, 0x1C, 0x0B, 0x52, 0x16, 0x51, 0x0F, 0x86, 0xC5,
			0x68, 0x9B, 0x21, 0x0C, 0x8B, 0x42, 0x87, 0xFF, 0x4F, 0xBE, 0xC8, 0xE8, 0xC7, 0xD4, 0x7A, 0xE0,
			0x55, 0x2F, 0x8A, 0x8E, 0xBA, 0x98, 0x37, 0xE4, 0xB2, 0x38, 0xA1, 0xB6, 0x32, 0x83, 0x3A, 0x7B,
			0x84, 0x3C, 0x61, 0xFB, 0x8C, 0x14, 0x3D, 0x43, 0x3B, 0x1D, 0xC3, 0xA2, 0x96, 0xB3, 0xF8, 0xC4,
			0xF2, 0x26, 0x2B, 0xD8, 0x7C, 0xFC, 0x23, 0x24, 0x66, 0xEF, 0x69, 0x64, 0x50, 0x54, 0x59, 0xF1,
			0xA0, 0x74, 0xAC, 0xC6, 0x7D, 0xB5, 0xE6, 0xE2, 0xC2, 0x7E, 0x67, 0x17, 0x5E, 0xE1, 0xB9, 0x3F,
			0x6C, 0x70, 0x08, 0x99, 0x45, 0x56, 0x76, 0xF9, 0x9A, 0x97, 0x19, 0x72, 0x5C, 0x02, 0x8F, 0x58,
		};
	uint8_t
		cur,
		checksum = 0,
		port = GetPort() ^ 0xCC;
	for (int i = 1; i != len; ++i)
	{
		// Alternate the mask every byte.
		cur = (uint8_t)src[i];
		if (!(i & 1))
			cur ^= port;
		cur = key[cur];
		checksum ^= cur & 0xAA;
		buffer_[i - 1] = cur;
	}
	if (src[0] != checksum)
		throw SAMPRakNetChecksumException(src[0], checksum);
	return buffer_;
}

uint8_t *
	SAMPRakNet::
	Encrypt(uint8_t const * src, int len)
{
	static const uint8_t
		key[256] = {
			0x27, 0x69, 0xFD, 0x87, 0x60, 0x7D, 0x83, 0x02, 0xF2, 0x3F, 0x71, 0x99, 0xA3, 0x7C, 0x1B, 0x9D,
			0x76, 0x30, 0x23, 0x25, 0xC5, 0x82, 0x9B, 0xEB, 0x1E, 0xFA, 0x46, 0x4F, 0x98, 0xC9, 0x37, 0x88,
			0x18, 0xA2, 0x68, 0xD6, 0xD7, 0x22, 0xD1, 0x74, 0x7A, 0x79, 0x2E, 0xD2, 0x6D, 0x48, 0x0F, 0xB1,
			0x62, 0x97, 0xBC, 0x8B, 0x59, 0x7F, 0x29, 0xB6, 0xB9, 0x61, 0xBE, 0xC8, 0xC1, 0xC6, 0x40, 0xEF,
			0x11, 0x6A, 0xA5, 0xC7, 0x3A, 0xF4, 0x4C, 0x13, 0x6C, 0x2B, 0x1C, 0x54, 0x56, 0x55, 0x53, 0xA8,
			0xDC, 0x9C, 0x9A, 0x16, 0xDD, 0xB0, 0xF5, 0x2D, 0xFF, 0xDE, 0x8A, 0x90, 0xFC, 0x95, 0xEC, 0x31,
			0x85, 0xC2, 0x01, 0x06, 0xDB, 0x28, 0xD8, 0xEA, 0xA0, 0xDA, 0x10, 0x0E, 0xF0, 0x2A, 0x6B, 0x21,
			0xF1, 0x86, 0xFB, 0x65, 0xE1, 0x6F, 0xF6, 0x26, 0x33, 0x39, 0xAE, 0xBF, 0xD4, 0xE4, 0xE9, 0x44,
			0x75, 0x3D, 0x63, 0xBD, 0xC0, 0x7B, 0x9E, 0xA6, 0x5C, 0x1F, 0xB2, 0xA4, 0xC4, 0x8D, 0xB3, 0xFE,
			0x8F, 0x19, 0x8C, 0x4D, 0x5E, 0x34, 0xCC, 0xF9, 0xB5, 0xF3, 0xF8, 0xA1, 0x50, 0x04, 0x93, 0x73,
			0xE0, 0xBA, 0xCB, 0x45, 0x35, 0x1A, 0x49, 0x47, 0x6E, 0x2F, 0x51, 0x12, 0xE2, 0x4A, 0x72, 0x05,
			0x66, 0x70, 0xB8, 0xCD, 0x00, 0xE5, 0xBB, 0x24, 0x58, 0xEE, 0xB4, 0x80, 0x81, 0x36, 0xA9, 0x67,
			0x5A, 0x4B, 0xE8, 0xCA, 0xCF, 0x9F, 0xE3, 0xAC, 0xAA, 0x14, 0x5B, 0x5F, 0x0A, 0x3B, 0x77, 0x92,
			0x09, 0x15, 0x4E, 0x94, 0xAD, 0x17, 0x64, 0x52, 0xD3, 0x38, 0x43, 0x0D, 0x0C, 0x07, 0x3C, 0x1D,
			0xAF, 0xED, 0xE7, 0x08, 0xB7, 0x03, 0xE6, 0x8E, 0xAB, 0x91, 0x89, 0x3E, 0x2C, 0x96, 0x42, 0xD9,
			0x78, 0xDF, 0xD0, 0x57, 0x5D, 0x84, 0x41, 0x7E, 0xCE, 0xF7, 0x32, 0xC3, 0xD5, 0x20, 0x0B, 0xA7,
		};
	uint8_t
		cur,
		checksum = 0,
		port = GetPort() ^ 0xCC;
	for (int i = 0; i != len; ++i)
	{
		// Alternate the mask every byte.
		cur = (uint8_t)src[i];
		checksum ^= cur & 0xAA;
		if (i & 1)
			cur ^= port;
		cur = key[cur];
		buffer_[i + 1] = cur;
	}
	buffer_[0] = checksum;
	return buffer_;
}

// cons
	SAMPRakNetChecksumException::
	SAMPRakNetChecksumException(uint8_t expected, uint8_t got)
:
	std::exception(),
	Expected(expected),
	Got(got)
{
}

char const *
	SAMPRakNetChecksumException::
	what() const noexcept
{
	return "RakNet decryption checksum mismatch";
}

void 
	SAMPRakNet::
	HandleQuery(SOCKET instance, int size, sockaddr_in const & client, char const* buffer)
{
	unsigned int bufferLength = 0;

	// Ping
	if (buffer[10] == 'p')
	{
		memcpy(sendBuffer, buffer, 10);
		bufferLength += 10;

		// Write 'p' signal and client ping
		WriteToSendBuffer(bufferLength, 'p');
		WriteToSendBuffer(bufferLength, *reinterpret_cast<unsigned int*>(const_cast<char*>(&buffer[11])));

		sendto(instance, sendBuffer, bufferLength, 0, reinterpret_cast<const sockaddr*>(&client), size);
		return;
	}

	// Server info
	else if (buffer[10] == 'i')
	{
		int serverNameLength = GetServerName().length();
		int gameModeNameLength = gameModeName.length();

		const std::string
			& languageName = (GetRules().find("language") != GetRules().end()) ? GetRules()["language"] : "";
		int languageNameLength = languageName.length();

		memcpy(sendBuffer, buffer, 10);
		bufferLength += 10;

		// Write `i` signal and player count details
		WriteToSendBuffer(bufferLength, static_cast<unsigned short>('i'));
		WriteToSendBuffer(bufferLength, GetPlayerCount());
		WriteToSendBuffer(bufferLength, GetMaxPlayers());

		// Write server name
		WriteToSendBuffer(bufferLength, static_cast<int>(serverNameLength));
		WriteToSendBuffer(GetServerName().c_str(), bufferLength, serverNameLength);
		
		// Write gamemode name
		WriteToSendBuffer(bufferLength, static_cast<int>(gameModeNameLength));
		WriteToSendBuffer(GetGameModeName().c_str(), bufferLength, gameModeNameLength);

		// Write language name (since 0.3.7, it was map name before that)
		WriteToSendBuffer(bufferLength, static_cast<int>(languageNameLength));
		WriteToSendBuffer(languageName.c_str(), bufferLength, languageNameLength);

		sendto(instance, sendBuffer, bufferLength, 0, reinterpret_cast<const sockaddr*>(&client), size);
		return;
	}

	// Players
	else if (buffer[10] == 'c')
	{
		memcpy(sendBuffer, buffer, 10); 
		bufferLength += 10;

		// Write 'c' signal and player count
		WriteToSendBuffer(bufferLength, static_cast<unsigned char>('c'));
		WriteToSendBuffer(bufferLength, GetPlayerCount());

		const auto & _players =
			GetPlayers();

		for (auto & player : _players)
		{
			// Write player name
			unsigned char playerNameLength = static_cast<unsigned char>(player.first.length());
			WriteToSendBuffer(bufferLength, playerNameLength);
			WriteToSendBuffer(player.first.c_str(), bufferLength, playerNameLength);

			// Write player score
			WriteToSendBuffer(bufferLength, player.second);
		}

		sendto(instance, sendBuffer, bufferLength, 0, reinterpret_cast<const sockaddr*>(&client), size);
		return;
	}

	// Rules
	else if (buffer[10] == 'r')
	{
		const auto & _rules = GetRules();
		memcpy(sendBuffer, buffer, 10);
		bufferLength += 10;

		// Write 'r' signal and rule count
		WriteToSendBuffer(bufferLength, static_cast<unsigned char>('r'));
		WriteToSendBuffer(bufferLength, static_cast<unsigned short>(_rules.size()));

		for (auto & rule : _rules)
		{
			// Wrtie rule name
			unsigned char ruleNameLength = static_cast<unsigned char>(rule.first.length());
			WriteToSendBuffer(bufferLength, ruleNameLength);
			WriteToSendBuffer(rule.first.c_str(), bufferLength, ruleNameLength);
			
			// Write rule value
			unsigned char ruleValueLength = static_cast<unsigned char>(rule.second.length());
			WriteToSendBuffer(bufferLength, ruleValueLength);
			WriteToSendBuffer(rule.second.c_str(), bufferLength, ruleValueLength);
		}

		sendto(instance, sendBuffer, bufferLength, 0, reinterpret_cast<const sockaddr*>(&client), size);
		return;
	}
}