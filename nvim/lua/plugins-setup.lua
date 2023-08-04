
local ensure_packer = function()
  local fn = vim.fn
  local install_path = fn.stdpath('data')..'/site/pack/packer/start/packer.nvim'
  if fn.empty(fn.glob(install_path)) > 0 then
    fn.system({'git', 'clone', '--depth', '1', 'https://github.com/wbthomason/packer.nvim', install_path})
    vim.cmd [[packadd packer.nvim]]
    return true
  end
  return false
end

local packer_bootstrap = ensure_packer()

vim.cmd([[
	augroup packer_user_config
		autocmd!
		autocmd BufWritePost plugins-setup.lua source <afile> | PackerSync
	augroup end
]])


return require('packer').startup(function(use)
  use 'wbthomason/packer.nvim'
  use 'folke/tokyonight.nvim'
  use {
    'nvim-lualine/lualine.nvim',
    requires = { 'nvim-tree/nvim-web-devicons', opt = true }
  }
  use {
    'nvim-tree/nvim-tree.lua',
    requires = {
      'nvim-tree/nvim-web-devicons', -- optional
    },
  }
  use("christoomey/vim-tmux-navigator")
  use "nvim-treesitter/nvim-treesitter"
  use "p00f/nvim-ts-rainbow"
  use {
      "williamboman/mason.nvim",
      "williamboman/mason-lspconfig.nvim",  -- 这个相当于mason.nvim和lspconfig的桥梁
      "neovim/nvim-lspconfig"
  }
  use "hrsh7th/nvim-cmp"
  use "hrsh7th/cmp-nvim-lsp"
  use "L3MON4D3/LuaSnip" -- snippets引擎，不装这个自动补全会出问题
  use "saadparwaiz1/cmp_luasnip"
  use "rafamadriz/friendly-snippets"
  use "hrsh7th/cmp-path" -- 文件路径


  use "numToStr/Comment.nvim" -- gcc和gc注释
  use "windwp/nvim-autopairs" -- 自动补全括号

  use "akinsho/bufferline.nvim" -- buffer分割线
  use "lewis6991/gitsigns.nvim" -- 左则git提示

  use {
    'nvim-telescope/telescope.nvim', tag = '0.1.1',  -- 文件检索
    requires = { {'nvim-lua/plenary.nvim'} }
  }
  use("szw/vim-maximizer") -- maximizes and restores current window
  use 'simrat39/symbols-outline.nvim' 
  use {"akinsho/toggleterm.nvim", tag = '*', config = function()
    require("toggleterm").setup()
    end}
  use "rcarriga/nvim-dap-ui"
  use "mfussenegger/nvim-dap"
  use "theHamsta/nvim-dap-virtual-text"





  --   use({
--     "glepnir/lspsaga.nvim",
--     opt = true,
--     branch = "main",
--     event = "LspAttach",
--     config = function()
--         require("lspsaga").setup({})
--     end,
--     requires = {
--         {"nvim-tree/nvim-web-devicons"},
--         --Please make sure you install markdown and markdown_inline parser
--         {"nvim-treesitter/nvim-treesitter"}
--     }
-- })


  if packer_bootstrap then
    require('packer').sync()
  end
end)
