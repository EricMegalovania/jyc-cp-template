// tex to README.md Git 
#include <bits/stdc++.h>
#include <fstream>
#include <locale>
#include <codecvt> // 在C++17已废弃，但仍可使用
#include <windows.h>
#include <local/dbg.h>

bool isTargetCommand(const std::string& cmd) {
	dbg(cmd);
	return cmd == "section" || cmd == "subsection" ||
	       cmd == "subsubsection" || cmd == "subsubsubsection";
}

void outputTitle(const std::string& command, const std::string& content) {
	if (command == "section") {
		std::cout << "- " << content << "\n";
	} else if (command == "subsection") {
		std::cout << "  - " << content << "\n";
	} else if (command == "subsubsection") {
		std::cout << "    - " << content << "\n";
	} else if (command == "subsubsubsection") {
		std::cout << "      - " << content << "\n";
	}
}

int main(int argc, char* argv[]) {
	using convert_type = std::codecvt_utf8<wchar_t>;
	
	// 创建转换器对象
	std::wstring_convert<convert_type, wchar_t> converter;
	
	// 示例宽字符串（含中文和特殊字符）
	std::wstring wstr = L"# <center>JYCの算法竞赛模板</center>\n\n## 包含的内容\n\n";
	
	try {
		// 将宽字符串转换为UTF-8字节序列
		std::string utf8_str = converter.to_bytes(wstr);
		
		// 以二进制模式写入文件（确保无编码转换）
		std::ofstream file("README.md", std::ios::binary);
		file.write(utf8_str.data(), utf8_str.size());
		file.close();
	}
	catch (const std::range_error& e) {
		// 处理转换错误（如无效Unicode字符）
		return 1;
	}
	
	freopen("./tex/main.tex", "r", stdin);
	freopen("./README.md", "a", stdout);
	
	int state = 0; // 初始状态
	std::string currentCommand; // 当前处理的命令
	std::string content = ""; // 存储标题内容
	int braceCounter = 0; // 花括号计数器
	char ch;
	while (1) {
		bool rd = 0;
		while ((ch = std::cin.get()) != EOF) {
			if (!std::isspace(ch) || ch == ' ') {
				rd = 1;
				break;
			}
		}
		if (!rd) break;
		switch (state) {
			case 0: // 普通状态
				if (ch == '\\') {
					state = 1; // 进入命令读取状态
					currentCommand = "";
				}
				// 忽略所有非命令字符
				break;
				
			case 1: // 读取命令名
				if (std::isalpha(static_cast<unsigned char>(ch))) {
					currentCommand += ch;
				} else {
					if (std::isspace(static_cast<unsigned char>(ch))) {
						state = 2; // 跳过空白字符
					} else if (ch == '{') {
						if (isTargetCommand(currentCommand)) {
							state = 3; // 进入内容读取状态
							braceCounter = 1;
							content = "";
						} else {
							state = 0; // 忽略非目标命令
						}
					}
					else if (ch == '\\') {
						currentCommand = "";
						state = 1;
					}
					else {
						state = 0; // 忽略非目标命令
					}
				}
				break;
				
			case 2: // 跳过空白字符
				if (std::isspace(static_cast<unsigned char>(ch))) {
					// 继续跳过空白
				} else if (ch == '{') {
					if (isTargetCommand(currentCommand)) {
						state = 3; // 开始读取内容
						braceCounter = 1;
						content = "";
					} else {
						state = 0; // 忽略非目标命令
					}
				} else {
					state = 0; // 忽略非目标命令
				}
				break;
				
			case 3: // 读取标题内容（正常模式）
				if (ch == '\\') {
					state = 4; // 进入转义模式
				} else if (ch == '{') {
					braceCounter++;
					content += ch;
				} else if (ch == '}') {
					braceCounter--;
					if (braceCounter == 0) {
						// 命令处理完成
						outputTitle(currentCommand, content);
						state = 0;
					} else {
						content += ch;
					}
				} else {
					content += ch;
				}
				break;
				
			case 4: // 读取标题内容（转义模式）
				content += '\\'; // 添加转义的反斜杠
				content += ch;
				state = 3; // 返回正常模式
				break;
		}
	}
	
	// 文件结束后的清理
	if (state == 3 || state == 4) {
		if (state == 4) {
			content += '\\'; // 处理未完成的转义
		}
		outputTitle(currentCommand, content);
	}
	std::cout << "\n";
	
	freopen("./TODO.md", "r", stdin);
	std::cin.clear();
	while ((ch = std::cin.get()) != EOF) {
		std::cout << ch;
	}
	
	// 添加自动 Git 提交功能
	if (argc == 2) { // 检查是否有额外命令行参数
		// 构建 Git 命令
		std::string gitAdd = "git add .";
		std::string gitCommit = "git commit -m \"" + std::string(argv[1]) + "\"";
		std::string gitPush = "git push";
		
		// 执行 Git 命令
		std::system(gitAdd.c_str());
		std::system(gitCommit.c_str());
		std::system(gitPush.c_str());
	}
	
	return 0;
}
