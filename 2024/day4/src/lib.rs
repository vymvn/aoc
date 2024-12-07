use std::fs::File;
use std::io::{self, BufRead};
use std::path::Path;

pub fn read_lines<P>(filename: P) -> io::Result<io::Lines<io::BufReader<File>>>
where
    P: AsRef<Path>,
{
    let file = File::open(filename)?;
    Ok(io::BufReader::new(file).lines())
}

pub fn check_bounds(i: usize, j: usize, board: &Vec<String>, word_length: usize) -> bool {
    println!("i: {}, j: {}", i, j);
    if i >= board.len() || j >= board[i].len() {
        println!("Out of bounds");
        return false;
    }

    if j + word_length >= board[i].len() {
        println!("Out of bounds");
        return false;
    }

    true
}

pub fn get_right(board: &Vec<String>, i: usize, j: usize, word_length: usize) -> String {
    if !check_bounds(i, j + word_length, board, word_length) {
        return "".to_string();
    }

    let check_word = board[i]
        .chars()
        .skip(j)
        .take(word_length)
        .collect::<String>();
    check_word
}

pub fn get_left(board: &Vec<String>, i: usize, j: usize, word_length: usize) -> String {
    if !check_bounds(i, j + word_length, board, word_length) {
        return "".to_string();
    }

    let check_word = board[i]
        .chars()
        .skip(j - word_length)
        .take(word_length)
        .collect::<String>();
    check_word.chars().rev().collect::<String>()
}
