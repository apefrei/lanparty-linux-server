:syntax on
:set tabstop=4
:set shiftwidth=4
:set expandtab 
:set autoindent
:set autoread
:set ruler
:set showmatch
:set encoding=utf8
:set paste
:set bg=dark

function! PositionCursorFromViminfo()
  if !(bufname("%") =~ '\(COMMIT_EDITMSG\)') && line("'\"") > 1 && line("'\"") <= line("$")
    exe "normal! g`\""
  endif
endfunction
:au BufReadPost * call PositionCursorFromViminfo()

