set fish_greeting

alias ls="exa"
alias la="ls --long --header --icons --all"
alias lg="ls --long --header --icons --git"
alias fd="fd -HI" #(1)


set -gx EDITOR nvim
set -Ux GTK_THEME "Catppuccin Macchiato"
set -gx LANG en_US.UTF-8


# uwsm
#if uwsm check may-start; then
#    exec uwsm start hyprland.desktop
#fi
