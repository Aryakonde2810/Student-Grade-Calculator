#include "mongoose.h"

static void event_handler(struct mg_connection *c, int ev,
                          void *ev_data)
{
    if (ev == MG_EV_HTTP_MSG)
    {
        struct mg_http_message *hm =
            (struct mg_http_message *) ev_data;

        if (mg_match(hm->uri, mg_str("/api/hello"), NULL))
        {
            mg_http_reply(c, 200,
                          "Content-Type: application/json\r\n",
                          "{\"status\":1}\n");
        }
        else
        {
            mg_http_reply(c, 404, "",
                          "Not Found\n");
        }
    }
}

int main(void)
{
    struct mg_mgr mgr;

    mg_mgr_init(&mgr);

    mg_http_listen(&mgr, "http://localhost:8000",
                   event_handler, NULL);

    printf("Server running at http://localhost:8000\n");

    for (;;)
    {
        mg_mgr_poll(&mgr, 1000);
    }

    mg_mgr_free(&mgr);
    return 0;
}