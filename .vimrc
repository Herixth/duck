" 2018/10/9 "

let $VIMRUNTIME="C:/Program Files/Git/usr/share/vim/vim81"


" Startup {{{
         filetype indent plugin on

         augroup ft_vim
            au!

            au FileType vim setlocal foldmethod=marker
         augroup END
" }}}

" General {{{
         set nocompatible
         set nobackup
         set noswapfile
         set history=1024
         set autochdir
         set whichwrap=b,s,<,>,[,]
         set nobomb
         set backspace=indent,eol,start whichwrap+=<,>,[,]
         " Vim 的默认寄存器和系统剪贴板共享
         set clipboard+=unnamed
         " 设置 alt 键不映射到菜单栏
         set winaltkeys=no
         " 禁止光标闪烁
         set gcr=a:block-blinkon0
" }}}

" Lang & Encoding {{{
         set fileencodings=utf-8,gbk2312,gbk,gb18030,cp936
         set encoding=utf-8
         set langmenu=zh_CN
         let $LANG = 'en_US.UTF-8'
 "language messages zh_CN.UTF-8
" }}}

" GUI {{{
        set background=dark
        colorscheme molokai
        set t_Co=256

        source $VIMRUNTIME/delmenu.vim
        source $VIMRUNTIME/menu.vim
        set cursorline
        set hlsearch
        set number
        " 窗口大小
        set lines=35 columns=100
        " 分割出来的窗口位于当前窗口下边/右边
        set splitbelow
        set splitright
        "不显示工具/菜单栏
        set guioptions-=T
        set guioptions-=m
        set guioptions-=L
        set guioptions-=r
        set guioptions-=b
        " 使用内置 tab 样式而不是 gui
        set guioptions-=e
        set nolist
        " set listchars=tab:▶\ ,eol:¬,trail:·,extends:>,precedes:<
        set guifont=YaHei\ Consolas\ Hybrid\ 11.5
        set nowrap
        let g:Powerline_colorshceme='solarized256'

        set tags="C:/Program Files/Git/usr/share/vim/vim81/ctags58"
        set autochdir
" }}}

" Format {{{
         set autoindent
         set smartindent
         set tabstop=4
         set expandtab
         set shiftwidth=4
         set softtabstop=4
         set foldmethod=indent
         syntax enable
         syntax on
         " 基于缩进或语法进行代码折叠
        "set foldmethod=indent
        set foldmethod=syntax
        " 启动 vim 时关闭折叠代码
        set nofoldenable
" }}}

" Key-map {{{
        imap <C-v> "+gP
        vmap <C-c> "+y
        vnoremap <BS> d
        vnoremap <C-C> "+y
        vnoremap <C-Insert> "+y
        imap <C-V>		"+gP
        map <S-Insert>		"+gP
        cmap <C-V>		<C-R>+
        cmap <S-Insert>		<C-R>+

        exe 'inoremap <script> <C-V>' paste#paste_cmd['i']
        exe 'vnoremap <script> <C-V>' paste#paste_cmd['v']
        " 定义快捷键的前缀，即<Leader>
        let mapleader=";"
        " 设置快捷键将选中文本块复制至系统剪贴板
        vnoremap <Leader>y "+y
        " 设置快捷键将系统剪贴板内容粘贴至 vim
        nmap <Leader>p "+p
        " 定义快捷键关闭当前分割窗口
        nmap <Leader>q :q<CR>
        " 定义快捷键保存当前窗口内容
        nmap <Leader>w :w<CR>
        " 定义快捷键保存所有窗口内容并退出 vim
        nmap <Leader>WQ :wa<CR>:q<CR>
        " 不做任何保存，直接退出 vim
        nmap <Leader>Q :qa!<CR>
        " 依次遍历子窗口
        nnoremap nw <C-W><C-W>
        " 跳转至右方的窗口
        nnoremap <Leader>lw <C-W>l
        " 跳转至左方的窗口
        nnoremap <Leader>hw <C-W>h
        " 跳转至上方的子窗口
        nnoremap <Leader>kw <C-W>k
        " 跳转至下方的子窗口
        nnoremap <Leader>jw <C-W>j
        " 定义快捷键在结对符之间跳转
        nmap <Leader>M %
" }}}

" vundle {{{
        filetype off
        set rtp+=~/.vim/bundle/Vundle.vim
        
        call vundle#begin()
        
        " ----- Vundle ----- {{{
        Plugin 'VundleVim/Vundle.vim'
        " }}}
        " ----- Molokai ----- {{{
        Plugin 'tomasr/molokai'
        " }}}za
        " ----- Cpp-enhanced-highlight ----- {{{
        Plugin 'octol/vim-cpp-enhanced-highlight'

        let g:cpp_class_scope_highlight = 1
        let g:cpp_member_variable_highlight = 1
        let g:cpp_class_decl_highlight = 1
        let g:cpp_experimental_simple_template_highlight = 1
        let g:cpp_concepts_highlight = 1
        let g:cpp_no_function_highlight = 1
        let c_no_curly_error=1
        "  }}}
        " ----- Indent-guides {{{
        Plugin 'nathanaelkane/vim-indent-guides'
        " 随 vim 自启动
        let g:indent_guides_enable_on_vim_startup=1
        " 从第二层开始可视化显示缩进
        let g:indent_guides_start_level=2
        " 色块宽度
        let g:indent_guides_guide_size=1
        " 快捷键 i 开/关缩进可视化
        :nmap <silent> <Leader>i <Plug>IndentGuidesToggle
        "  }}}
        " ----- Fswitch ----- {{{
        Plugin 'derekwyatt/vim-fswitch'
        
        " *.cpp 和 *.h 间切换
       " nmap <silent> <Leader>sw :FSHere<cr>
        map <C-n> :FSHere<cr>
        "  }}}
        "  ----- Tagbar ----- {{{
        Plugin 'majutsushi/tagbar'

        
        "let g:tagbar_ctags_bin="C":/'Program Files'/Git/usr/share/vim/vim81/ctags58"
        map <C-m> :TagbarToggle<CR>         
        set tags=tags;
        set autochdir
        " 设置 tagbar 子窗口的位置出现在主编辑区的左边 
        let tagbar_left=1 
        " 设置显示／隐藏标签列表子窗口的快捷键。速记：identifier list by tag
        nnoremap <Leader>ilt :TagbarToggle<CR> 
        " 设置标签子窗口的宽度 
        let tagbar_width=32 
        " tagbar 子窗口中不显示冗余帮助信息 
        let g:tagbar_compact=1
        " 设置 ctags 对哪些代码标识符生成标签
        let g:tagbar_type_cpp = {
            \ 'kinds' : [
                 \ 'c:classes:0:1',
                 \ 'd:macros:0:1',
                 \ 'e:enumerators:0:0', 
                 \ 'f:functions:0:1',
                 \ 'g:enumeration:0:1',
                 \ 'l:local:0:1',
                 \ 'm:members:0:1',
                 \ 'n:namespaces:0:1',
                 \ 'p:functions_prototypes:0:1',
                 \ 's:structs:0:1',
                 \ 't:typedefs:0:1',
                 \ 'u:unions:0:1',
                 \ 'v:global:0:1',
                 \ 'x:external:0:1'
             \ ],
             \ 'sro'        : '::',
             \ 'kind2scope' : {
                 \ 'g' : 'enum',
                 \ 'n' : 'namespace',
                 \ 'c' : 'class',
                 \ 's' : 'struct',
                 \ 'u' : 'union'
             \ },
             \ 'scope2kind' : {
                 \ 'enum'      : 'g',
                 \ 'namespace' : 'n',
                 \ 'class'     : 'c',
                 \ 'struct'    : 's',
                 \ 'union'     : 'u'
             \ }
        \ }        
        " 正向遍历同名标签
        nmap <Leader>tn :tnext<CR>
        " 反向遍历同名标签
        nmap <Leader>tp :tprevious<CR>
        "  }}}
        "  ----- Nerdcommenter ----- {{{
        Plugin 'scrooloose/nerdcommenter'

        " Add spaces after comment delimiters by default
        let g:NERDSpaceDelims = 1

        " Use compact syntax for prettified multi-line comments
        let g:NERDCompactSexyComs = 1

        " Align line-wise comment delimiters flush left instead of following code indentation
        let g:NERDDefaultAlign = 'left'

        " Set a language to use its alternate delimiters by default
        let g:NERDAltDelims_java = 1

        " Add your own custom formats or override the defaults
        let g:NERDCustomDelimiters = { 'c': { 'left': '/**','right': '*/' } }

        " Allow commenting and inverting empty lines (useful when commenting a region)
        let g:NERDCommentEmptyLines = 1

        " Enable trimming of trailing whitespace when uncommenting
        let g:NERDTrimTrailingWhitespace = 1

        " Enable NERDCommenterToggle to check all selected lines is commented or not 
        let g:NERDToggleCheckAllLines = 1
        "  }}}

        call vundle#end()
        
        filetype plugin indent on
" }}}
