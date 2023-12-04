/*
 *  This file is part of nzbget. See <https://nzbget.com>.
 *
 *  Copyright (C) 2023 Denis <denis@nzbget.com>
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

#ifndef EXTENSION_MANAGER_H
#define EXTENSION_MANAGER_H

#include <vector>
#include "Extension.h"

namespace ExtensionManager
{
	using Extension = Extension::Script;
	using Extensions = std::vector<Extension>;

	class Manager
	{
	public:
		Manager() = default;
		~Manager() = default;

		const Extensions& GetExtensions() const;

	private:
		void LoadExtensions(const char* directory, bool isSubDir);
		void CreateTasks();

		Extensions m_extensions;
	};
}

extern ExtensionManager::Manager* g_extensionManager;

#endif
