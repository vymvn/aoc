use day4::get_left;
use day4::get_right;
use day4::read_lines;
use std::env;

pub const WORD: &str = "XMAS";

fn main() {
    let args: Vec<String> = env::args().collect();

    let filename = match args.get(1).map(String::as_str) {
        Some("test") => "test_input.txt",
        Some("real") => "input.txt",
        _ => {
            eprintln!("usage: {} [test|real]", args[0]);
            return;
        }
    };

    if let Ok(lines) = read_lines(filename) {
        let board: Vec<String> = lines.filter_map(Result::ok).collect();
        dbg!(&board);

        for i in 0..board.len() {
            for j in 0..board[i].len() {
                let curr_char = board[i].chars().nth(j).unwrap();

                if curr_char == 'X' {
                    println!("X at ({}, {})", i, j);
                    println!(
                        "Word at right of X: {}",
                        get_right(&board, i, j, WORD.len())
                    );
                    println!("Word at left of X: {}", get_left(&board, i, j, WORD.len()));

                    //println!("X at ({}, {})", i, j);
                    //println!(
                    //    "right of X {}",
                    //    board.get(i).expect("empty").chars().nth(j + 10).unwrap()
                    //);
                    //println!("left of X {}", board[i].chars().nth(j - 1).unwrap());
                    //println!("bottom of X {}", board[i + 1].chars().nth(j).unwrap());
                    //println!("top of X {}", board[i - 1].chars().nth(j).unwrap());
                    //println!(
                    //    "top right of X {}",
                    //    board[i - 1].chars().nth(j + 1).unwrap()
                    //);
                    //println!("top left of X {}", board[i - 1].chars().nth(j - 1).unwrap());
                    //println!(
                    //    "bottom right of X {}",
                    //    board[i + 1].chars().nth(j + 1).unwrap()
                    //);
                    //println!(
                    //    "bottom left of X {}",
                    //    board[i + 1].chars().nth(j - 1).unwrap()
                    //);

                    //println!("found X at ({}, {})", i, j);
                    //let check_word = board[i]
                    //    .chars()
                    //    .skip(j)
                    //    .take(WORD.len())
                    //    .collect::<String>();
                    //println!("check_word: {}", check_word);
                }
            }
        }

        dbg!(&board);
    }
}
