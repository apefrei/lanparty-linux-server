# Source global definitions
if [ -f /etc/bashrc ]; then
    . /etc/bashrc
fi

export LS_OPTIONS='--color=auto'
eval "`dircolors`"

alias "vi"="vim"
alias ".."="cd .."
alias ls="ls $LS_OPTIONS"
alias ll="ls $LS_OPTIONS -l"
alias l="ls $LS_OPTIONS -al"
alias logtail="cd /var/log; tail -f cron dmesg maillog messages secure"

export PS1="\[\033[01;34m\]\u@\[\033[01;31m\]\h\[\033[00m\]:\w # "
export EDITOR="vim"

if test -f ~/.bashrc_local
then
        source ~/.bashrc_local
fi

case "$TERM" in
    screen*) PROMPT_COMMAND='echo -ne "\033k\033\0134"'
esac

# eof
