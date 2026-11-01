#include "mongoose.h"
#include "calculator.h"

static const char *cors_headers =
    "Access-Control-Allow-Origin: *\r\n"
    "Access-Control-Allow-Methods: POST, OPTIONS\r\n"
    "Access-Control-Allow-Headers: Content-Type\r\n";

static void event_handler(struct mg_connection *c, int ev,
                          void *ev_data)
{
    if (ev != MG_EV_HTTP_MSG)
        return;

    struct mg_http_message *hm =
        (struct mg_http_message *) ev_data;

    // Handle browser preflight requests
    if (mg_match(hm->method, mg_str("OPTIONS"), NULL))
    {
        mg_http_reply(c, 204, cors_headers, "");
        return;
    }

    if (mg_match(hm->uri, mg_str("/api/calculate"), NULL))
    {
        if (!mg_match(hm->method, mg_str("POST"), NULL))
        {
            mg_http_reply(c, 405, cors_headers,
                          "Method not allowed\n");
            return;
        }

        int marks[SUBJECT_COUNT];
        double value;

        for (int i = 0; i < SUBJECT_COUNT; i++)
        {
            char path[10];
            snprintf(path, sizeof(path), "$[%d]", i);

            if (!mg_json_get_num(hm->body, path, &value) ||
                value < 0 || value > 100 ||
                value != (int)value)
            {
                mg_http_reply(c, 400,
                    "Content-Type: application/json\r\n"
                    "Access-Control-Allow-Origin: *\r\n",
                    "{\"error\":\"Enter five valid marks between 0 and 100\"}\n");
                return;
            }

            marks[i] = (int)value;
        }

        GradeResult result = calculateGrade(marks);

        mg_http_reply(c, 200,
            "Content-Type: application/json\r\n"
            "Access-Control-Allow-Origin: *\r\n",
            "{\"total\":%d,\"percentage\":%.2f,"
            "\"grade\":\"%c\",\"passed\":%s}\n",
            result.total,
            result.percentage,
            result.grade,
            result.passed ? "true" : "false");
    }
    else
    {
        mg_http_reply(c, 404, cors_headers, "Not found\n");
    }
}

int main(void)
{
    struct mg_mgr mgr;

    mg_mgr_init(&mgr);

    const char *port = getenv("PORT");

if (port == NULL)
    port = "8000";

char address[100];

snprintf(address, sizeof(address),
         "http://0.0.0.0:%s", port);

mg_http_listen(&mgr, address, event_handler, NULL);

    printf("C Grade Calculator running on port 8000\n");

    for (;;)
        mg_mgr_poll(&mgr, 1000);

    mg_mgr_free(&mgr);
    return 0;
}