"
" Vundle
"
set nocompatible              " be iMproved, required
filetype off                  " required

" set the runtime path to include Vundle and initialize
set rtp+=~/.vim/bundle/Vundle.vim
call vundle#begin()
" alternatively, pass a path where Vundle should install plugins
"call vundle#begin('~/some/path/here')

" let Vundle manage Vundle, required
Plugin 'VundleVim/Vundle.vim'

"
" Keep Plugin commands between vundle#begin/end.
"
Plugin 'scrooloose/nerdtree'
Plugin 'altercation/vim-colors-solarized'
Plugin 'vim-airline/vim-airline'
Plugin 'vim-syntastic/syntastic'
Plugin 'tpope/vim-fugitive'
"Plugin 'xolox/vim-easytags'
Plugin 'majutsushi/tagbar'
Plugin 'terryma/vim-multiple-cursors'

" All of your Plugins must be added before the following line
call vundle#end()            " required
filetype plugin indent on    " required
" To ignore plugin indent changes, instead use:
"filetype plugin on
"
" Brief help
" :PluginList       - lists configured plugins
" :PluginInstall    - installs plugins; append `!` to update or just :PluginUpdate
" :PluginSearch foo - searches for foo; append `!` to refresh local cache
" :PluginClean      - confirms removal of unused plugins; append `!` to auto-approve removal
"
" see :h vundle for more details or wiki for FAQ
" Put your non-Plugin stuff after this line


"
" Set powerline fonts for airline
"
let g:airline_powerline_fonts = 1


"
" NERDTree handling
"
" Open NERDTree on file opening
autocmd vimenter * NERDTree
autocmd VimEnter * wincmd p
" Close vi if only NERDTree is left open
autocmd bufenter * if (winnr("$") == 1 && exists("b:NERDTree") && b:NERDTree.isTabTree()) | q | endif
" Toggle NERDTree
nmap <silent> <C-d> :NERDTreeToggle<CR>


"
" Syntastic handling
"
set statusline+=%#warningmsg#
set statusline+=%{SyntasticStatuslineFlag()}
set statusline+=%*

let g:syntastic_always_populate_loc_list = 1
let g:syntastic_auto_loc_list = 1
let g:syntastic_check_on_open = 1
let g:syntastic_check_on_wq = 0


"
" Tagbar handling
"
nnoremap <C-f> :TagbarToggle<CR>


"
" Handling lines
"
" Set hybrid line numbers
set number relativenumber
" Color of the current line
hi CursorLine   cterm=NONE ctermbg=8 ctermfg=white guibg=darkred guifg=white
" Color of line numbers
hi LineNr         ctermfg=DarkMagenta guifg=#2b506e guibg=#000000
" Color of current line number
hi CursorLineNr   term=bold ctermfg=Yellow gui=bold guifg=Yellow
set cursorline
" Setting scroll to always show some lines
set scrolloff=5
" Removing autocomment after a commented line
autocmd FileType * setlocal formatoptions-=c formatoptions-=r formatoptions-=o
" Do NOT SHOW complete line if it goes beyond the end of the terminal size
set nowrap


"
" Handling pastes
"
" Share clipboard buffers
set clipboard=unnamed
set paste


"
" Remap switching between splits with Ctrl+dir
"
nnoremap <C-left> <C-W><left>
nnoremap <C-right> <C-W><right>
nnoremap <C-up> <C-W><up>
nnoremap <C-down> <C-W><down>


"
" Resize split window horizontally and vertically
" 
" Shortcuts to Shift-Alt-Up - Alt is mapped as M in vim
nmap <silent> <S-M-Up> :2winc+<cr>
imap <silent> <S-M-Up> <Esc>:2winc+<cr>i
nmap <silent> <S-M-Down> :2winc-<cr>
imap <silent> <S-M-Down> <Esc>:2winc-<cr>i

nmap <silent> <S-M-Left> :2winc><cr>
imap <silent> <S-M-Left> <Esc>:2winc><cr>i
nmap <silent> <S-M-Right> :2winc<<cr>
imap <silent> <S-M-Right> <Esc>:2winc<<cr>i


"
" Maximize gvim
"
if has("gui_running")
  set lines=999 columns=999
endif


"
" Set tabs to 4 spaces
"
set expandtab
set shiftwidth=4
set softtabstop=4


"
" Highlight trailing whitespaces
"
highlight ExtraWhitespace ctermbg=yellow guibg=yellow
autocmd BufWinEnter * match ExtraWhitespace /\s\+$/


"
" Set colorscheme
"
syntax enable
set background=dark
let g:solarized_termcolors=256
colorscheme solarized
" Set transparent background
"hi Normal guibg=NONE ctermbg=NONE


"
" Handling searchs
"
set hlsearch
hi Search cterm=NONE ctermfg=black ctermbg=8
" Clear current search highlight by double tapping //
nmap <silent> // :nohlsearch<CR>
" Better search
set ignorecase
set smartcase
