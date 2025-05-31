#include <apirouter/apirouter.hpp>

using namespace apirouter;

int main()
{ 
    apirouter::server srv(80);

    apirouter::router wiki_router{ "/wiki" };
    apirouter::router base{"/"};
    
    wiki_router.get("/edit/page",
        [] (const http::request&) -> http::response
        {
        
            return {"You got the edit/page page\n"};
        }
    );

    wiki_router.get("/user/insert",
        [] (const http::request&) -> http::response 
        {
            return { "You got the user/insert page\n" };
        }
    );

    base.get("/",
        [](const http::request&) -> http::response
        {
            return {
R"html(
<!DOCTYPE html>
<html>
    <head>
        <title>Welcome to APIRouter++!</title>
    </head>
    <body>
        <div style="width: 75%; margin: auto; text-align: center">
            <h3>Welcome to APIRouter++!</h3>
        </div>
    </body>
</html>

)html"           
            };
        }
    );

    srv.include_router(wiki_router);
    srv.include_router(base);
    srv.run();




}