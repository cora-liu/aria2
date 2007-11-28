/* <!-- copyright */
/*
 * aria2 - The high speed download utility
 *
 * Copyright (C) 2006 Tatsuhiro Tsujikawa
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
 *
 * In addition, as a special exception, the copyright holders give
 * permission to link the code of portions of this program with the
 * OpenSSL library under certain conditions as described in each
 * individual source file, and distribute linked combinations
 * including the two.
 * You must obey the GNU General Public License in all respects
 * for all of the code used other than OpenSSL.  If you modify
 * file(s) with this exception, you may extend this exception to your
 * version of the file(s), but you are not obligated to do so.  If you
 * do not wish to do so, delete this exception statement from your
 * version.  If you delete this exception statement from all source
 * files in the program, then also delete it here.
 */
/* copyright --> */
#ifndef _D_DISK_ADAPTOR_H_
#define _D_DISK_ADAPTOR_H_

#include "BinaryStream.h"
#include "FileEntry.h"
#include "Logger.h"
#include "FileAllocationIterator.h"

class DiskAdaptor:public BinaryStream {
protected:
  string storeDir;
  FileEntries fileEntries;
  const Logger* logger;
public:
  DiskAdaptor();
  virtual ~DiskAdaptor();

  virtual void openFile() = 0;

  virtual void closeFile() = 0;

  virtual void openExistingFile() = 0;

  virtual void initAndOpenFile() = 0;

  virtual void onDownloadComplete() = 0;  

  virtual bool fileExists() = 0;

  virtual string getFilePath() = 0;

  virtual int64_t size() const = 0;

  // optional behavior
  virtual void truncate(int64_t length) {}

  void setFileEntries(const FileEntries& fileEntries) {
    this->fileEntries = fileEntries;
  }

  FileEntryHandle getFileEntryFromPath(const string& fileEntryPath) const;

  const FileEntries& getFileEntries() const { return fileEntries; }

  bool addDownloadEntry(const string& fileEntryPath);

  bool addDownloadEntry(int index);

  void addAllDownloadEntry();

  void removeAllDownloadEntry();

  void setStoreDir(const string& storeDir) { this->storeDir = storeDir; }

  const string& getStoreDir() const { return this->storeDir; }

  virtual FileAllocationIteratorHandle fileAllocationIterator() = 0;

  virtual void enableDirectIO() {};

  virtual void disableDirectIO() {};
};

typedef SharedHandle<DiskAdaptor> DiskAdaptorHandle;

#endif // _D_DISK_ADAPTOR_H_
