#ifndef CONFIG_H    // "if CONFIG_H has NOT been defined yet to prevent multiple inclusions"
#define CONFIG_H   // "define CONFIG_H and include everything below it until the #endif"

typedef struct {
    char *default_backend;

    /* Sendmail configuration */
    char *sendmail_path;

    /* SMTP configuration */
    char *smtp_host;
    char *smtp_port;
    char *smtp_user;
    char *smtp_password;
    char *smtp_tls;

    /* REST */
    char *rest_provider_url;
    char *rest_api_key;
} Config;

void print_config(Config *config);

#endif // CONFIG_H