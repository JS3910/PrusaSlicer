#ifndef slic3r_Utils_hpp_
#define slic3r_Utils_hpp_

#include <locale>

namespace Slic3r {

extern void set_logging_level(unsigned int level);
extern void trace(unsigned int level, const char *message);

// Set a path with GUI resource files.
void set_var_dir(const std::string &path);
// Return a full path to the GUI resource files.
const std::string& var_dir();
// Return a full resource path for a file_name.
std::string var(const std::string &file_name);

// Set a path with various static definition data (for example the initial config bundles).
void set_resources_dir(const std::string &path);
// Return a full path to the resources directory.
const std::string& resources_dir();

// Set a path with GUI localization files.
void set_local_dir(const std::string &path);
// Return a full path to the localization directory.
const std::string& localization_dir();

// Set a path with preset files.
void set_data_dir(const std::string &path);
// Return a full path to the GUI resource files.
const std::string& data_dir();

// A special type for strings encoded in the local Windows 8-bit code page.
// This type is only needed for Perl bindings to relay to Perl that the string is raw, not UTF-8 encoded.
typedef std::string local_encoded_string;

// Convert an UTF-8 encoded string into local coding.
// On Windows, the UTF-8 string is converted to a local 8-bit code page.
// On OSX and Linux, this function does no conversion and returns a copy of the source string.
extern local_encoded_string encode_path(const char *src);
extern std::string decode_path(const char *src);
extern std::string normalize_utf8_nfc(const char *src);

// File path / name / extension splitting utilities, working with UTF-8,
// to be published to Perl.
namespace PerlUtils {
    // Get a file name including the extension.
    extern std::string path_to_filename(const char *src);
    // Get a file name without the extension.
    extern std::string path_to_stem(const char *src);
    // Get just the extension.
    extern std::string path_to_extension(const char *src);
    // Get a directory without the trailing slash.
    extern std::string path_to_parent_path(const char *src);
};

// Timestamp formatted for header_slic3r_generated().
extern std::string timestamp_str();
// Standard "generated by Slic3r version xxx timestamp xxx" header string, 
// to be placed at the top of Slic3r generated files.
inline std::string header_slic3r_generated() { return std::string("generated by " SLIC3R_FORK_NAME " " SLIC3R_VERSION " " ) + timestamp_str(); }

// Encode a file into a multi-part HTTP response with a given boundary.
std::string octoprint_encode_file_send_request_content(const char *path, bool select, bool print, const char *boundary);

// Compute the next highest power of 2 of 32-bit v
// http://graphics.stanford.edu/~seander/bithacks.html
template<typename T>
inline T next_highest_power_of_2(T v)
{
	if (v != 0)
	    -- v;
    v |= v >> 1;
    v |= v >> 2;
    v |= v >> 4;
    if (sizeof(T) >= sizeof(uint16_t))
    	v |= v >> 8;
    if (sizeof(T) >= sizeof(uint32_t))
	    v |= v >> 16;
    if (sizeof(T) >= sizeof(uint64_t))
	    v |= v >> 32;
    return ++ v;
}

} // namespace Slic3r

#endif // slic3r_Utils_hpp_