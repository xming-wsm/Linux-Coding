local opt = vim.opt
opt.number = true
opt.clipboard:append("unnamedplus")
opt.mouse:append("a")

opt.wrap = false

opt.tabstop = 2
opt.shiftwidth = 2
opt.expandtab = true
opt.autoindent = true

opt.cursorline = true
opt.splitright = true
opt.splitbelow = true
opt.ignorecase = true
opt.smartcase = true
opt.termguicolors = true
opt.signcolumn = "yes"


vim.cmd[[colorscheme tokyonight-moon]]
