use day4::read_lines;
use std::env;

// directions enum
enum Direction {
    Right,
    Left,
    Top,
    Bottom,
    TopRight,
    BottomRight,
    TopLeft,
    BottomLeft,
}

impl Direction {
    fn offset(&self) -> (isize, isize) {
        match self {
            Direction::Right => (0, 1),
            Direction::Left => (0, -1),
            Direction::Top => (-1, 0),
            Direction::Bottom => (1, 0),
            Direction::TopRight => (-1, 1),
            Direction::BottomRight => (1, 1),
            Direction::TopLeft => (-1, -1),
            Direction::BottomLeft => (1, -1),
        }
    }
}

fn search_direction(
    board: &Vec<String>,
    row: usize,
    col: usize,
    direction: &Direction,
    word: &str,
) -> bool {
    let (row_offset, col_offset) = direction.offset();

    let mut curr_row = row as isize;
    let mut curr_col = col as isize;
    let mut chars = word.chars();

    // This skips the first letter if the word is longer than 1
    // This is because we want to skip the X in XMAS but still be able to use the function for one
    // character if needed
    if word.len() > 1 {
        chars.next();
    }

    for char_to_match in chars {
        // Skip 'X' as it's already matched
        curr_row += row_offset;
        curr_col += col_offset;

        // Check bounds
        if curr_row < 0
            || curr_row >= board.len() as isize
            || curr_col < 0
            || curr_col >= board[curr_row as usize].len() as isize
        {
            return false;
        }

        // Match the next character in WORD
        if board[curr_row as usize].chars().nth(curr_col as usize) != Some(char_to_match) {
            return false;
        }
    }

    true
}

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

        let mut xmas_count = 0;
        let mut x_mas_patterns = 0;

        // Iterate through the board
        for row in 0..board.len() {
            for col in 0..board[row].len() {
                let curr_char = board[row].chars().nth(col).unwrap();

                if curr_char == 'X' {
                    for direction in [
                        Direction::Right,
                        Direction::Left,
                        Direction::Top,
                        Direction::Bottom,
                        Direction::TopRight,
                        Direction::BottomRight,
                        Direction::TopLeft,
                        Direction::BottomLeft,
                    ] {
                        if search_direction(&board, row, col, &direction, "XMAS") {
                            xmas_count += 1;
                        }
                    }
                }

                // I'm sorry
                if curr_char == 'A' {
                    if (search_direction(&board, row, col, &Direction::TopRight, "S")
                        && search_direction(&board, row, col, &Direction::BottomLeft, "M")
                        || search_direction(&board, row, col, &Direction::TopRight, "M")
                            && search_direction(&board, row, col, &Direction::BottomLeft, "S"))
                        && (search_direction(&board, row, col, &Direction::TopLeft, "S")
                            && search_direction(&board, row, col, &Direction::BottomRight, "M")
                            || search_direction(&board, row, col, &Direction::TopLeft, "M")
                                && search_direction(&board, row, col, &Direction::BottomRight, "S"))
                    {
                        x_mas_patterns += 1;
                    }
                }
            }
        }

        println!("Found \"XMAS\" {} times", xmas_count);
        println!("Found \"X-MAS\" pattern {} times", x_mas_patterns);
    }
}
