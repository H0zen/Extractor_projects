#include "Storage.h"
#include <cstdio>

namespace MPQLoader
{
    Storage::~Storage() 
    {
        std::printf("In StormStrage destructor\n");
        Free();
    }

    void Storage::PrintLastErrMsg(const std::string& when)
    {
        std::printf("[ERROR]@%s: error code: %d\n", when.c_str(), GetLastError());
    }


    bool Storage::Load(const FileList& mpqList, const FileList& archiveList)
    {
        HANDLE mpqHandle;
        for (FileList::const_iterator it = mpqList.begin(); it != mpqList.end(); ++it)
        {
            if (!SFileOpenArchive((*it).c_str(), 0, MPQ_OPEN_READ_ONLY, &mpqHandle))
            {
                PrintLastErrMsg(std::string("Storage::InitStorage: ") + *it);
                return false;
            }
            m_store.push_back(mpqHandle);
        }
        return true;
    }

    void Storage::Free()
    {
        std::printf("In Storage::FreeStorage\n");

        for (ArchiveSet::const_iterator it = m_store.begin(); it != m_store.end(); ++it)
            SFileCloseArchive(*it);

        m_store.clear();
    }

    bool Storage::OpenFile(const std::string& fileName, HANDLE& handle){return true;}

    bool Storage::ReadFile(HANDLE& handle, ACE_UINT8* buff, size_t size){return true;}

    bool Storage::ExtractFile(HANDLE& handle, std::string& outFileName){return true;}

    void Storage::CloseFile(HANDLE& handle){}


    template <class Worker> 
    void Storage::DoForAllFileType(const std::string extension, Worker& worker){}

}

