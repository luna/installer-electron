#pragma once

#include <QDir>
#include <QFile>

#include "errors.h"

const auto InstallerAppDirName = "lunaInstallerApp";

// these path are relative to qrc root or temporary directory
#if __linux__
const auto ConsoleInstallerExecPath = "lunaInstallerApp/resources/app/consoleInstaller";
const auto InstallerExecPath = "lunaInstallerApp/lunaInstaller";
const auto LibNodeDllPath = "lunaInstallerApp/libnode.so";
#elif __MINGW32__
const auto ConsoleInstallerExecPath = "lunaInstallerApp/resources/app/consoleInstaller.exe";
const auto InstallerExecPath = "lunaInstallerApp/lunaInstaller.exe";
const auto LibNodeDllPath = "lunaInstallerApp/node.dll";
#endif

void recursiveCopy(const QDir &copiedDir, const QDir &destination);

template<class... Paths>
void setExecPermissionsInFiles(const Paths &... paths)
{
	auto setExecPermission = [&](const auto &path)
	{
		QFile file(path);
		if (!file.setPermissions(QFileDevice::ReadUser | QFileDevice::ExeUser))
			throw SettingPermissionError(path.toStdString());
	};
	struct Dummy{} dummy[] = { (setExecPermission(paths), Dummy{})... };
}
