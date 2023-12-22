/*
 * exec_all.cpp
 *
 *  Created on: Jul 29, 2017
 *      Author: nullifiedcat
 */

#include "ipcb.hpp"
#include "cathookipc.hpp"

#include <string>
#include <stdio.h>

void ReplaceString(std::string& input, const std::string& what, const std::string& with_what) {
	size_t index;
	index = input.find(what);
	while (index != std::string::npos) {
		input.replace(index, what.size(), with_what);
		index = input.find(what, index + with_what.size());
	}
}

int main(int argc, const char** argv) {
	std::string cmd = "";
	if (argc < 1) return 1;

	for (int i = 1; i < argc; i++) {
		cmd += (std::string(argv[i]) + " ");
	}

	cat_ipc::Peer<server_data_s, user_data_s> peer("cathook_followbot_server", false, false);
	peer.Connect();

	printf("ALL] %s\n", cmd.c_str());

	ReplaceString(cmd, " && ", " ; ");
	if (cmd.length() >= 63) {
		peer.SendMessage(0, -1, ipc_commands::execute_client_cmd_long, cmd.c_str(), cmd.length() + 1);
	} else {
		peer.SendMessage(cmd.c_str(), -1, ipc_commands::execute_client_cmd, 0, 0);
	}
}
