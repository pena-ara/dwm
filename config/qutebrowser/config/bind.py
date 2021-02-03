config.bind(",m", "hint links spawn mpv {hint-url}")
config.bind(",da", "hint links spawn st -e youtube-dl --extract-audio --audio-format mp3 -o '%(title)s.%(ext)s' {hint-url}")
