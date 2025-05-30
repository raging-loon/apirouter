#include <apirouter/apirouter.hpp>
#include <apirouter/routing/radix.hpp>

#include <apirouter/routing/router.hpp>
#include <apirouter/generic/str_util.hpp>
int main()
{ 
    apirouter::server srv(80);

    apirouter::generic::split_to_str("/wiki/page/edit/",'/');
    apirouter::router wiki_router{"/wiki"};
    
    wiki_router.add_route("/edit/page",
        []() {
        
            printf("You got the edit/page page\n");
        }
    );

    wiki_router.add_route("/user/insert",
        []() {
            printf("You got the user/insert page\n");
        }
    );

    srv.include_router(wiki_router);
    srv.run();

    auto node = srv.m_route_tree.search({"wiki","user", "insert"});

    if (node && node->get_callback())
    {
        (node->get_callback())();
    }
}