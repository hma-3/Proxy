#include <iostream>
#include <unordered_map>

using namespace std;

class YouTubeLibrary {
public:
    virtual void requestVideoInfo(const string& videoId) const = 0;
    virtual void downloadVideo(const string& videoId) const = 0;
};

class YouTubeLibraryImpl : public YouTubeLibrary {
public:
    void requestVideoInfo(const string& videoId) const override {
        cout << "Requesting video information for video ID: " << videoId << endl;
    }

    void downloadVideo(const string& videoId) const override {
        cout << "Downloading video for video ID: " << videoId << endl;
    }
};

class YouTubeLibraryProxy : public YouTubeLibrary {
    mutable YouTubeLibrary* youtubeLibrary;
    mutable unordered_map<string, string> videoInfoCache;
public:
    YouTubeLibraryProxy() : youtubeLibrary(nullptr) {}

    void requestVideoInfo(const string& videoId) const override {
        if (!youtubeLibrary) {
            youtubeLibrary = new YouTubeLibraryImpl();
        }

        youtubeLibrary->requestVideoInfo(videoId);

        videoInfoCache[videoId] = "Cached Video Information";
    }

    void downloadVideo(const string& videoId) const override {
        if (!youtubeLibrary) {
            youtubeLibrary = new YouTubeLibraryImpl();
        }

        youtubeLibrary->downloadVideo(videoId);
    }    
};

int main() {
    YouTubeLibraryProxy youtubeProxy;

    youtubeProxy.requestVideoInfo("video1");
    youtubeProxy.downloadVideo("video1");

    youtubeProxy.requestVideoInfo("video1");

    return 0;
}