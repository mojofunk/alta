ProjectDirectory::ProjectDirectory(const fs::path& project_path)
    : m_root_path(project_path)
{
}

bool ProjectDirectory::create()
{
	bool is_new = false;

	for (auto const& sub_dir : sub_directories()) {
		if (fs::create_directories(sub_dir)) {
			is_new = true;
		}
	}

	return is_new;
}

bool ProjectDirectory::is_valid() const
{
	if (!fs::is_directory(m_root_path)) return false;

	for (auto const& sub_dir : sub_directories()) {
		if (!fs::is_directory(sub_dir)) {
			return false;
		}
	}
	return true;
}

const fs::path ProjectDirectory::audiofiles_path() const
{
	return m_root_path / audiofiles_dir_name;
}

const fs::path ProjectDirectory::peak_path() const
{
	return m_root_path / peak_dir_name;
}

const std::vector<fs::path> ProjectDirectory::sub_directories() const
{
	std::vector<fs::path> tmp_paths;

	tmp_paths.push_back(audiofiles_path());
	tmp_paths.push_back(peak_path());

	return tmp_paths;
}
