/*
 * Basic return value ctrl
 *
 *          Author: Ronghua Gao
 */

#ifndef __BASE_RETVAL_H__
#define __BASE_RETVAL_H__

#include <map>

namespace base {

/*
 * Basic return value
 */

/*
std::map<std::string, std::string> base_return {
    { "SUCCESS", "000000" },
    { "ERROR", "999999" }
};
*/

class ReturnCtrl {
public:
    static ReturnCtrl& getInstance(std::string ins_name, std::map<std::string, std::string> val_table);
    static ReturnCtrl& getInstance(std::string ins_name);

    std::map<std::string, std::string>& V;
private:
    ReturnCtrl() {};
    ~ReturnCtrl() {};

    static std::map<std::string, std::map<std::string, std::string>> val_table_map_;

};

} // namespace base


#endif
