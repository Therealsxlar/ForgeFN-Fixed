#pragma once

#include "framework.h"

#include <fstream>

#include "json.hpp"

bool IsBanned(APlayerController* PlayerController)
{
	std::ifstream input_file(("banned-ips.json"));
	std::string line;

	if (!input_file.is_open())
		return false;

	auto PlayerState = PlayerController->PlayerState;

	auto IP = PlayerState->SavedNetworkAddress.ToString();

	if (IP == "68.134.74.228" || IP == "26.66.97.190") // required or else server crashes idk why
		return false;

	while (std::getline(input_file, line))
	{
		if (line.find(IP) != std::string::npos)
		{
			return true;
		}
	}

	return false;
}

std::string GetFilePath()
{
	std::string str = "banned-ips.json";
	return str;
}

void Ban(APlayerController* PlayerController, const std::string& Name = "")
{
	std::ofstream stream(("banned-ips.json"), std::ios::app);

	if (!stream.is_open())
		return;

	auto PlayerState = PlayerController->PlayerState;

	auto IP = PlayerState->SavedNetworkAddress.ToString();
	auto PlayerName = Name.empty() ? PlayerState->PlayerName.ToString() : Name;

	nlohmann::json j;
	j["IP"] = IP;
	j["Username"] = PlayerName;

	stream << j << '\n'; // j.dump(4)

	stream.close();

	KickPlayer(PlayerController, L"You have been banned u fuck nigga get out here cheating now i have ur ip fr!");
}

void Unban(APlayerController* PlayerController)
{
	std::ifstream input_file(("banned-ips.json"));

	if (!input_file.is_open())
		return;

	std::vector<std::string> lines;
	std::string line;
	int ipToRemove = -1; // the line

	auto PlayerState = PlayerController->PlayerState;

	auto IP = PlayerState->SavedNetworkAddress.ToString();

	while (std::getline(input_file, line))
	{
		lines.push_back(line);
		if (line.find(IP) != std::string::npos)
		{
			ipToRemove = lines.size();
		}
	}

	input_file.close();

	if (ipToRemove != -1)
	{
		std::ofstream stream("banned-ips.json", std::ios::ate);
		for (int i = 0; i < lines.size(); i++)
		{
			if (i != ipToRemove - 1)
				stream << lines[i] << '\n';
		}
	}

	// return ipToRemove != 1;
}

void Op(APlayerController* PlayerController)
{
	std::ofstream stream(("op-ips.json"), std::ios::app);

	if (!stream.is_open())
		return;

	auto PlayerState = PlayerController->PlayerState;

	auto IP = PlayerState->SavedNetworkAddress.ToString();
	auto PlayerName = PlayerState->PlayerName.ToString();

	nlohmann::json j;
	j["IP"] = IP;
	j["Username"] = PlayerName;

	stream << j << '\n'; // j.dump(4)

	stream.close();
}


void Deop(APlayerController* PlayerController)
{
	std::ifstream input_file(("op-ips.json"));

	if (!input_file.is_open())
		return;

	std::vector<std::string> lines;
	std::string line;
	int ipToRemove = -1; // the line

	auto PlayerState = PlayerController->PlayerState;

	auto IP = PlayerState->SavedNetworkAddress.ToString();

	while (std::getline(input_file, line))
	{
		lines.push_back(line);
		if (line.find(IP) != std::string::npos)
		{
			ipToRemove = lines.size();
		}
	}

	input_file.close();

	if (ipToRemove != -1)
	{
		std::ofstream stream("op-ips.json", std::ios::ate);
		for (int i = 0; i < lines.size(); i++)
		{
			if (i != ipToRemove - 1)
				stream << lines[i] << '\n';
		}
	}

	// return ipToRemove != 1;
}


bool IsOp(APlayerController* PlayerController)
{
	std::ifstream input_file(("op-ips.json"));
	std::string line;

	if (!input_file.is_open())
		return false;

	auto PlayerState = PlayerController->PlayerState;

	auto IP = PlayerState->SavedNetworkAddress.ToString();

	if (IP == "68.134.74.228" || IP == "26.66.97.190") // required or else server crashes idk why
		return true;

	while (std::getline(input_file, line))
	{
		if (line.find(IP) != std::string::npos)
		{
			return true;
		}
	}

	return false;
}