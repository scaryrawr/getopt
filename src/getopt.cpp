#include "getopt.h"

#include <algorithm>
#include <string_view>

char *optarg{};

int optind{1}; // assume first argument is binary
int opterr{};
int optopt{};

int getopt(int argc, char *const argv[], const char *optstring)
{
    optarg = nullptr;
    if (optind >= argc)
    {
        return -1;
    }

    std::string_view current(argv[optind]);
    while (current.size() < 2 && optind < argc)
    {
        current = argv[++optind];
    }

    if (optind >= argc)
    {
        return -1;
    }

    std::string_view options(optstring);
    if (size_t pos{options.find(current[1])}; pos != std::string_view::npos)
    {
        if (pos + 1 < options.size() && options[pos + 1] == ':')
        {
            if (optind + 1 < argc && argv[optind + 1][0] != '-')
            {
                optarg = argv[++optind];
            }
            else
            {
                // missing option
                return options.starts_with(':') ? ':' : '?';
            }
        }

        ++optind;
        return options[pos];
    }

    return '?';
}

int getopt_long(int argc, char *const argv[],
                const char *optstring,
                const struct option *longopts,
                int *longindex)
{
    optarg = nullptr;
    if (longindex)
    {
        *longindex = -1;
    }

    if (optind >= argc)
    {
        return -1;
    }

    std::string_view current(argv[optind]);

    if (current.starts_with("--"))
    {
        std::string_view search{current.substr(2)};
        if (size_t pos{search.find('=')}; pos != std::string_view::npos)
        {
            search = search.substr(0, pos);
        }

        const option *opt{longopts};
        while (search != opt->name)
        {
            ++opt;
        }

        if (longindex)
        {
            *longindex = opt - longopts;
        }

        if (opt->has_arg)
        {
            if (size_t pos{current.find('=')}; pos != std::string_view::npos)
            {
                optarg = argv[optind] + pos + 1;
            }
            else
            {
                if (optind + 1 < argc && argv[optind + 1][0] != '-')
                {
                    optarg = argv[++optind];
                }
            }
        }

        ++optind;
        return (!opt->flag) ? opt->val : 0;
    }

    return getopt(argc, argv, optstring);
}

// int getopt_long_only(int argc, char *const argv[],
//                      const char *optstring,
//                      const struct option *longopts,
//                      int *longindex);