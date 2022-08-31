export module MoWin:Platform;

#ifdef _WIN64
export import :Platform.Win64.Unicode;
export import :Platform.Win64.MBCS;
#endif