#include <apirouter/apirouter.hpp>
#include <format>
using namespace apirouter;

int main()
{ 
    apirouter::server srv(80);

    apirouter::router base{"/"};
    
    unsigned int times = 0;
    base.get("/",
        [&times](const http::request&) -> http::response
        {
            times++;
            return { std::format(
R"html(
<!DOCTYPE html>
<html>
    <head>
        <title>Welcome to APIRouter++!</title>
    </head>
    <body>
        <div style="width: 75%; margin: auto; text-align: center">
            <h3>Welcome to APIRouter++!</h3>
            <p>This page has been retrieved {} times<p>
        </div>
    </body>
</html>

)html"
            , times) };
        }
    );

    srv.include_router(base);
    srv.run();




}