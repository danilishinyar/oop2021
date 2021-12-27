#include "Artifact.h"



void Artifact::activate(Characteristics<std::string, float> &tb_src, Characteristics<std::string, float> &tb_dst) {
    tb_src = tb_src + tb_dst;
}

void Artifact::deactivate(Characteristics<std::string, float> &tb_src, Characteristics<std::string, float> &tb_dst) {
    tb_src = tb_src - tb_dst;
}