#include <apirouter/apirouter.hpp>
#include <apirouter/routing/radix.hpp>

#include <apirouter/routing/router.hpp>
#include <apirouter/generic/str_util.hpp>
int main()
{
    apirouter::server srv(80);

    //srv.run();
    apirouter::generic::split_to_str("/wiki/page/edit/",'/');
    apirouter::router wiki_router{"/wiki"};
    
    wiki_router.add_route("/edit/page",
        []() {}
    );

    wiki_router.add_route("/user/insert",
        []() {}
    );

    srv.include_router(wiki_router);

    auto node = srv.m_route_tree.search({"wiki","user"});

    if (node)
        printf("%s\n", node->get_children().front().get_segment().c_str());
}