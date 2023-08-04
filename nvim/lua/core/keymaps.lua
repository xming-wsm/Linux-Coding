vim.g.mapleader = " "


local kp = vim.keymap

kp.set("i", "jk", "<Esc>")

kp.set("v", "J", ":m '>+1<CR>gv=gv")
kp.set("v", "K", ":m '<-2<CR>gv=gv")

kp.set("n", "<leader>sm", ":MaximizerToggle<CR>") -- toggle split window maximization
kp.set("n", "<leader>sv", "<C-w>v")
kp.set("n", "<leader>sh", "<C-w>s")
kp.set("n", "<leader>sx", ":close<cr>")

kp.set("n", "<leader>nh", ":nohl<CR>")
kp.set("n", "<leader>e", ":NvimTreeToggle<CR>")



kp.set("n", "<leader>h", ":bprevious<CR>")
kp.set("n", "<leader>l", ":bnext<CR>")
kp.set("n", "<leader>c", ":BufferLineCloseOthers<CR>")
