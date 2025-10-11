#include <iostream>
#include <filesystem>
#include <string>
#include <cstdlib>
#include <system_error>

namespace fs = std::filesystem;

int main(int argc, char* argv[]) {
	if (argc != 2) {
		std::cerr << "Usage: ac_combiner <cpp_file>\n";
		return 1;
	}
	
	fs::path inputPath(argv[1]);
	
	fs::path originalDir = fs::current_path();
	// 如果输入路径是相对路径，则转换为基于当前工作目录的绝对路径
	if (inputPath.is_relative()) {
		inputPath = originalDir / inputPath;
	}
	
	if (!fs::exists(inputPath)) {
		std::cerr << "Error: File does not exist\n";
		return 1;
	}
	
	const fs::path acLibraryDir = "D:\\A_devcpp\\ac-library";
	const fs::path expanderPath = acLibraryDir / "expander.py";
	
	// 在执行 Python 命令前切换到 AtCoder Library 目录
	fs::current_path(acLibraryDir);
	
	// 构建并执行 Python 命令，添加 --lib 参数
	std::string command = "python \"" + expanderPath.string() + "\" --lib \"" + 
	acLibraryDir.string() + "\" \"" + inputPath.string() + "\"";
	int result = std::system(command.c_str());
	
	if (result != 0) {
		std::cerr << "Python script execution failed\n";
		return 1;
	}
	
	// 切换回原始目录
	fs::current_path(originalDir);
	
	// 检查生成的 combined.cpp（现在在 acLibraryDir 目录中）
	const fs::path combinedPath = acLibraryDir / "combined.cpp";
	if (!fs::exists(combinedPath)) {
		std::cerr << "Error: combined.cpp not generated\n";
		return 1;
	}
	
	// 准备目标路径
	fs::path outputPath = inputPath.parent_path() / 
	(inputPath.stem().string() + "_combined" + inputPath.extension().string());
	
	// 移动并重命名文件
	std::error_code ec;
	fs::rename(combinedPath, outputPath, ec);
	if (ec) {
		std::cerr << "Error moving file: " << ec.message() << "\n";
		return 1;
	}
	
	std::cout << "Successfully created: " << outputPath.string() << "\n";
	return 0;
}
