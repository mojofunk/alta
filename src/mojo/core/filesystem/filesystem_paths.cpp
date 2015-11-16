MOJO_DEBUG_DOMAIN(FILESYSTEM_PATHS);

fs::path get_user_config_directory()
{
	return g_get_user_config_dir();
}

fs::path get_user_data_directory()
{
	return g_get_user_data_dir();
}

paths_t get_system_data_directories()
{
	paths_t tmp;
	const char* const* dirs;

	dirs = g_get_system_data_dirs();

	if (dirs == NULL) return tmp;

	for (int i = 0; dirs[i] != NULL; i++) {
		tmp.push_back(dirs[i]);
	}

	return tmp;
}

paths_t get_system_config_directories()
{
	paths_t tmp;
	const char* const* dirs;

	dirs = g_get_system_config_dirs();

	if (dirs == NULL) return tmp;

	for (int i = 0; dirs[i] != NULL; i++) {
		tmp.push_back(dirs[i]);
	}

	return tmp;
}

fs::path user_config_directory()
{
	return fs::path(get_user_config_directory()) / PROGRAM_DIR_NAME;
}

fs::path installation_directory()
{
#ifdef MOJO_WINDOWS
	return g_win32_get_package_installation_directory_of_module(NULL);
#else
	// TODO?
	return fs::path();
#endif
}

Searchpath mojo_search_path()
{
	return Searchpath(mojo::getenv("MOJO_PATH"));
}

Searchpath system_config_search_path()
{
	Searchpath sp(get_system_config_directories());
	sp / PROGRAM_DIR_NAME;
	return sp;
}

Searchpath system_data_search_path()
{
	Searchpath sp(get_system_data_directories());
	sp / PROGRAM_DIR_NAME;
	return sp;
}

Searchpath module_search_path()
{
#ifdef MOJO_WINDOWS
	return installation_directory() / "bin";
#else
	return mojo_search_path();
#endif
}
