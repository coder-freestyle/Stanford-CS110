#include <sys/types.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <unistd.h>
#include "imdb.h"

#include <string.h>
#include <algorithm>
#include <iterator>
using namespace std;

const char *const imdb::kActorFileName = "actordata";
const char *const imdb::kMovieFileName = "moviedata";
imdb::imdb(const string& directory) {
	const string actorFileName = directory + "/" + kActorFileName;
	const string movieFileName = directory + "/" + kMovieFileName;  
	actorFile = acquireFileMap(actorFileName, actorInfo);
	movieFile = acquireFileMap(movieFileName, movieInfo);
}

bool imdb::good() const {
	return !( (actorInfo.fd == -1) || 
			(movieInfo.fd == -1) ); 
}

imdb::~imdb() {
	releaseFileMap(actorInfo);
	releaseFileMap(movieInfo);
}

// template<class ForwardIt, class T, class Compare=std::less<> >
// forwardIt binary_find(ForwardIt first, ForwardIt last, const T& value, Compare comp={})
// {
// Note: BOTH type T and the type after ForwardIt is dereferenced 
// must be implicitly convertible to BOTH Type1 and Type2, used in Compare. 
// This is stricter than lower_bound requirement (see above)

bool imdb::getCredits(const string& player, vector<film>& films) const {
}

bool imdb::getCast(const film& movie, vector<string>& players) const { 
}

const void *imdb::acquireFileMap(const string& fileName, struct fileInfo& info) {
	struct stat stats;
	stat(fileName.c_str(), &stats);
	info.fileSize = stats.st_size;
	info.fd = open(fileName.c_str(), O_RDONLY);
	return info.fileMap = mmap(0, info.fileSize, PROT_READ, MAP_SHARED, info.fd, 0);
}

void imdb::releaseFileMap(struct fileInfo& info) {
	if (info.fileMap != NULL) munmap((char *) info.fileMap, info.fileSize);
	if (info.fd != -1) close(info.fd);
}
