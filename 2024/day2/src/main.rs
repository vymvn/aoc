use std::fs::File;
use std::io::{self, BufRead};
use std::path::Path;

#[derive(Debug)]
struct Report {
    levels: Vec<u8>,
}

fn read_lines<P>(filename: P) -> io::Result<io::Lines<io::BufReader<File>>>
where
    P: AsRef<Path>,
{
    let file = File::open(filename)?;
    Ok(io::BufReader::new(file).lines())
}

fn main() {
    let mut reports: Vec<Report> = Vec::new();

    if let Ok(lines) = read_lines("./test_input.txt") {
        for line in lines.flatten() {
            let nums: Vec<u8> = line
                .split_whitespace()
                .filter_map(|s| s.parse::<u8>().ok())
                .collect();

            let report = Report { levels: nums };

            reports.push(report);
        }
    }

    for report in &reports {
        println!("{:?}", report);
    }
}
