#ifndef LAB3_REFACTORED_ARTIFACT_H
#define LAB3_REFACTORED_ARTIFACT_H

#include "Characteristics.h"
#include <string>

class Artifact {
public:
    Artifact() = default;;
    void activate(Characteristics<std::string, float>& tb_src, Characteristics<std::string, float>& tb_dst);
    void deactivate(Characteristics<std::string, float>& tb1_src, Characteristics<std::string, float>& tb_dst);
};


#endif //LAB3_REFACTORED_ARTIFACT_H
