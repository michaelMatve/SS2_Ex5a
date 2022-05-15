#include "doctest.h"
#include "OrgChart.hpp"

TEST_CASE("good inputs"){

    //creat new OrgChart named university and insert nuodes into it
    ariel::OrgChart university;
      university.add_root("yossi")
    .add_sub("yossi", "mosh")
    .add_sub("mosh", "noam")         
    .add_sub("yossi", "michal")        
    .add_sub("mosh", "nofar") 
    .add_sub("yossi", "mordi")
    .add_sub("michal", "shimon")
    .add_sub("michal", "sasi")
    .add_sub("michal", "sharon")
    .add_sub("sasi", "daniel");
    //creat vector order by level_order of the object aboth
    std::vector<std::string> level_university;
    level_university.push_back("yossi");
    level_university.push_back("mosh");
    level_university.push_back("michal");
    level_university.push_back("mordi");
    level_university.push_back("noam");
    level_university.push_back("nofar");
    level_university.push_back("shimon");
    level_university.push_back("sasi");
    level_university.push_back("sharon");
    level_university.push_back("daniel");
    ulong level_counter = 0;
    //check if the order is the same as exeptd
    for (auto level_it = university.begin_level_order(); level_it != university.end_level_order(); ++level_it)
    {
        CHECK((*level_it)== level_university[level_counter]);
        ++level_counter;
    }
    // new vector with the same names in revers order
    std::vector<std::string> revers_university;
    revers_university.push_back("daniel");
    revers_university.push_back("noam");
    revers_university.push_back("nofar");
    revers_university.push_back("shimon");
    revers_university.push_back("sasi");
    revers_university.push_back("sharon");
    revers_university.push_back("mosh");
    revers_university.push_back("michal");
    revers_university.push_back("mordi");
    revers_university.push_back("yossi");
    
    ulong revers_counter = 0;

    //check if the order is the same as exeptd
    for (auto rever_it = university.begin_reverse_order(); rever_it != university.reverse_order(); ++rever_it)
    {
        CHECK((*rever_it)== revers_university[revers_counter]);
        ++revers_counter;
    }
//new vector with predetor order
std::vector<std::string> prev_university;
    prev_university.push_back("yossi");
    prev_university.push_back("mosh");
    prev_university.push_back("noam");
    prev_university.push_back("nofar");

    prev_university.push_back("michal");
    prev_university.push_back("shimon");
    prev_university.push_back("sasi");

    prev_university.push_back("daniel");
    prev_university.push_back("sharon");

    prev_university.push_back("mordi");

    ulong prev_counter = 0;
    //check if the order is the same as exeptd
    for (auto pred_it=university.begin_preorder(); pred_it!=university.end_preorder(); ++pred_it) 
    {
      CHECK((*pred_it)== prev_university[prev_counter]);
      ++prev_counter;
    } 

}

TEST_CASE("bad inputs"){
    //check that the func doesnt add f the node not exist
    ariel::OrgChart university;
    CHECK_THROWS(university.add_sub("yossi", "mosh"));

    university.add_root("yossi");
    CHECK_THROWS(university.add_sub("michal", "mosh"));
    //check that the func doesnt add f the node not exist
    university.add_sub("yossi", "mosh")
    .add_sub("mosh", "noam")         
    .add_sub("yossi", "michal")        
    .add_sub("mosh", "nofar") 
    .add_sub("yossi", "mordi")
    .add_sub("michal", "shimon")
    .add_sub("michal", "sasi")
    .add_sub("michal", "sharon")
    .add_sub("sasi", "daniel");
    CHECK_THROWS(university.add_sub("sasiiids", "mosh"));


    
}