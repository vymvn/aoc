use regex::Regex;
use std::env;
use std::fs::File;
use std::io::{self, BufRead};
use std::path::Path;

static mut MUL_ENABLED: bool = true;

fn read_lines<P>(filename: P) -> io::Result<io::Lines<io::BufReader<File>>>
where
    P: AsRef<Path>,
{
    let file = File::open(filename)?;
    Ok(io::BufReader::new(file).lines())
}

fn mul(x: i32, y: i32) -> i32 {
    x * y
}

fn parse_instruction(cap: &regex::Captures) -> Option<(i32, i32)> {
    if let (Ok(x), Ok(y)) = (cap[1].parse::<i32>(), cap[2].parse::<i32>()) {
        Some((x, y))
    } else {
        None
    }
}

fn find_instructions_plus_plus(line: String) -> Vec<(i32, i32)> {
    let mut results: Vec<(i32, i32)> = Vec::new();

    // unholy regex++ to match "mul(x,y)" and "do()" and "don't()"
    let re = Regex::new(r"mul\((\d+),\s*(\d+)\)|do\(\)|don't\(\)").unwrap();

    for cap in re.captures_iter(&line) {
        unsafe {
            match &cap[0] {
                "do()" => {
                    MUL_ENABLED = true;
                }
                "don't()" => {
                    MUL_ENABLED = false;
                }
                _ => {
                    if MUL_ENABLED {
                        if let Some((x, y)) = parse_instruction(&cap) {
                            results.push((x, y));
                        }
                    }
                }
            }
        }
    }

    results
}

fn find_instructions(line: String) -> Vec<(i32, i32)> {
    let mut results: Vec<(i32, i32)> = Vec::new();

    // unholy regex to match "mul(x, y)"
    let re = Regex::new(r"mul\((-?\d+),\s*(-?\d+)\)").unwrap();

    for cap in re.captures_iter(&line) {
        if let Some((x, y)) = parse_instruction(&cap) {
            results.push((x, y));
        }
    }

    results
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

    let mut sums: Vec<i32> = Vec::new();

    if let Ok(lines) = read_lines(filename) {
        for line in lines.flatten() {
            let instructions = find_instructions_plus_plus(line); // change to find_instructions()
                                                                  // for part 1
            let sum: i32 = instructions.iter().map(|(x, y)| mul(*x, *y)).sum();
            sums.push(sum);
            println!("sum: {}", sum);
        }
        println!("total sum: {}", sums.iter().sum::<i32>());
    }
}
