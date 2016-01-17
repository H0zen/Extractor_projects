#ifndef __I_STORAGE_H__
#define __I_STORAGE_H__

#include <string>
#include <vector>
#include <deque>

#include "Define.h"
#include "StormLib.h"

namespace MPQLoader
{
    class Storage
    {
        typedef std::vector<std::string> FileList;
        typedef std::deque<HANDLE> ArchiveSet;

        public:
            ~Storage();
            bool Load(const FileList& mpqList, const FileList& patchList);
            void Free();

            bool OpenFile(const std::string& fileName, HANDLE& handle);
            bool ReadFile(HANDLE& handle, ACE_UINT8* buffer, size_t size);
            bool ExtractFile(HANDLE& handle, std::string& outFileName);
            void CloseFile(HANDLE& handle);

            template <class Worker> void DoForAllFileType(const std::string extension, Worker& worker);
        private:
            void PrintLastErrMsg(const std::string& when);
            // list of mpq files for lookup most recent file version
            ArchiveSet m_store;
    };
}
#endif
