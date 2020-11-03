#include <getopt.h>
#include <cassert>
#include <string_view>

int main(int, char const **)
{
    const char *const argv[] = {"bin",
                                "--longopteq=myarg",
                                "--longopt",
                                "otherarg",
                                "-d",
                                "dir",
                                "-f"};
    int argc{sizeof(argv) / sizeof(*argv)};

    static option options[] = {
        {"longopteq", required_argument, nullptr, 0},
        {"longopt", required_argument, nullptr, 0}};

    int index{};
    int code{};
    bool dir{};
    bool f{};
    bool longopteq{};
    bool longopt{};
    while ((code = getopt_long(argc, (char *const *)argv, "d:f", options, &index)) >= 0)
    {
        switch (code)
        {
        case ':':
        case '?':
            assert(false);
            break;
        case 'd':
        {
            std::string_view view(optarg);
            dir = true;
            assert(view == "dir");
            break;
        }
        case 'f':
        {
            f = true;
            break;
        }
        }

        switch (index)
        {
        case 0:
        {
            std::string_view view(optarg);
            longopteq = true;
            assert(view == "myarg");
            break;
        }
        case 1:
        {
            std::string_view view(optarg);
            longopt = true;
            assert(view == "otherarg");
            break;
        }
        }
    }

    assert(dir);
    assert(f);
    assert(longopteq);
    assert(longopt);

    return 0;
}
