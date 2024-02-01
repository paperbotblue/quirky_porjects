const prompt = require("prompt-sync")();

const ROWS = 3;
const COLS = 3;

const SYMBOLS_COUNT = {
  "A": 2,
  "B": 4,
  "C": 6,
  "D": 8
}

const SYMBOLS_VALUES = {
  "A": 5,
  "B": 4,
  "C": 3,
  "D": 2
}

function deposit()
{
  while(true)
  {
    const input = prompt("Enter a deposit amount: ");
    const deposit_amount = parseFloat(input);
    if(isNaN(deposit_amount) || deposit_amount <= 0)
    {
      console.log("that is not a valid number retard");
      deposit();
    }
    else
    {
      return deposit_amount;
    }
  }
}

function get_number_of_lines()
{
  while(true)
  {
    const input = prompt("Enter number of lines you wish to bet on: ");
    const number_of_lines = parseFloat(input);
    if(isNaN(number_of_lines) || number_of_lines > 3 || number_of_lines <= 0)
    {
      console.log("Not a valid input retard");
    }
    else
    {
      return number_of_lines;
    }
  }
}

function get_bet(balance, number_of_lines)
{
  while(true)
  {
    const bet = prompt("Enter the total bet: ");
    const bet_amount = parseFloat(bet);
    if(isNaN(bet_amount) || bet_amount > balance / number_of_lines || bet_amount <= 0)
    {
      console.log("Not a valid bet retard");
    }
    else
    {
      return bet_amount;
    }
  }
}

function spin()
{
  const symbols = [];
  for(const [symbol, count] of Object.entries(SYMBOLS_COUNT))
  {
    for(let i = 0 ; i < count ; ++i)
    {
      symbols.push(symbol);
    }
  }
  const reels = [];
  for(let i = 0 ; i < COLS ; ++i)
  {
    reels.push([]);
    const reel_symbols = [...symbols];
    for(let j = 0 ; j < ROWS ; ++j)
    {
      const random_index = Math.floor(Math.random() * reel_symbols.length);
      const selected_symbol = reel_symbols[random_index];
      reels[i].push(selected_symbol);
      reel_symbols.splice(random_index, 1);
    }
  }
  return reels;
}

function transpose(reels)
{
  const rows = [];
  for(let i = 0 ; i < ROWS ; ++i)
  {
    rows.push([]);
    for(let j = 0 ; j < COLS ; ++j)
    {
      rows[i].push(reels[j][i]);
    }
  }
  return rows;
}

function print_rows(rows)
{
  console.log(rows);
  for(const row of rows)
  {
    let str = "";
    for(let i = 0 ; i < ROWS ; ++i)
    {
      str+="|" + row[i];
    }
    str+="|";
    console.log(str);
  }

}

function get_winnings(rows, bet, lines)
{
  let winnings = 0;
  for(let row = 0 ; row < lines ; ++row)
  {
    const symbols = rows[row];
    let win = true;
    for (const symbol of symbols)
    {
      if (symbol != symbols[0])
      {
        win = false;
      }
    }
    if(win) 
    {
      winnings += bet*SYMBOLS_VALUES[symbols[0]];
    }
  }
  return winnings;
}

function get_play_status()
{
  while(true)
  {
    const input = prompt("do you wish to continue(y/n)? ");
    if(input == "y")
    {
      return true;
    }
    else
    {
      return false;
    }
  }
}

let balance = deposit();
let quit = false;
while (!quit)
{
  const number_on_lines = get_number_of_lines();
  const bet = get_bet(balance, number_on_lines);
  balance-=bet*number_on_lines;
  const reel = spin();
  const rows = transpose(reel);
  print_rows(rows);
  const winnings = get_winnings(rows,bet,number_on_lines);
  balance+=winnings;
  console.log("You win, $" + winnings.toString());
  console.log("You have $ " + balance.toString() + "left");
  if(balance <= 0 || !get_play_status())
  {
    quit = true;
  }
}