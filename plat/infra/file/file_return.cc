#include "file_return.h"

namespace file {

FileRet::ECodeMapType FileRet::ECodeMap = {
    { ECode::FILE_ESTATE, "" },
    { ECode::FILE_EACCES, "" },
    { ECode::FILE_EFAULT, "" },
    { ECode::FILE_EINVAL, "" },
    { ECode::FILE_EIO, "" },
    { ECode::FILE_ELOOP, "" },
    { ECode::FILE_ENAMETOOLONG, "" },
    { ECode::FILE_ENOENT, "" },
    { ECode::FILE_ENOMEM, "" },
    { ECode::FILE_ENOTDIR, "" },
    { ECode::FILE_EMODE, "" }
};

}
