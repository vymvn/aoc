/**
 * The fact that this code works is proof that god left us
 **/
use std::cmp::Ordering;
use std::fs::File;
use std::io::{self, BufRead};
use std::path::Path;

struct Report {
    levels: Vec<i8>,
    safe: bool,
}

fn apply_problem_dampener(levels: &Vec<i8>, problem_index: usize) -> Vec<i8> {
    let mut new_levels = levels.clone();
    new_levels.remove(problem_index);
    new_levels
}

fn is_safe(levels: &Vec<i8>, problem_dampener: bool) -> bool {
    // JUST ONE MORE VARIABLE BRO I CAN QUIT ANYTIME JUST ONE MORE
    let mut safe = false;
    let mut increasing: bool = false;
    let mut decreasing: bool = false;
    let mut max_diff: i8 = 0;
    let mut same_direction: bool = false;

    // Check first 2 elements to see if they are increasing or decreasing
    // loop through the rest of the elements and check if it keeps increasing or decreasing
    // if it does, then it's safe
    // if it doesn't, then it's not safe
    // if it's not increasing or decreasing, then it's not safe

    // get() does bound checked indexing so don't have to worry if array is empty
    match (levels.get(0), levels.get(1)) {
        (Some(&first), Some(&second)) => match first < second {
            true => increasing = true,
            false => decreasing = true,
        },
        _ => eprintln!("Error: one of the levels is fucking empty? :sob:"),
    }

    for i in 0..levels.len() - 1 {
        match levels[i].cmp(&levels[i + 1]) {
            Ordering::Less => {
                if increasing {
                    same_direction = true;
                } else {
                    same_direction = false;
                    break;
                }
            }
            Ordering::Greater => {
                if decreasing {
                    same_direction = true;
                } else {
                    same_direction = false;
                    break;
                }
            }
            Ordering::Equal => {
                same_direction = false;
                break;
            }
        }

        let diff = (levels[i] - levels[i + 1]).abs();

        if diff > max_diff {
            max_diff = diff;
        }
    }

    // real g check
    if same_direction && max_diff <= 3 {
        safe = true;
    }

    if !safe && problem_dampener {
        for i in 0..levels.len() {
            let applied_dampener: Vec<i8> = apply_problem_dampener(&levels, i);
            //println!("=====================");
            //println!("Problem index: {}", i);
            //println!("Levels: {:?}", levels);
            //println!("Applied dampener: {:?}", applied_dampener);
            if is_safe(&applied_dampener, false) {
                //println!("Safe after dampener removed {}", i);
                safe = true;
            } else {
                //println!("Not safe after dampener removed {}", i);
                //println!("=====================\n")
            }
        }
    }

    safe
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

    //if let Ok(lines) = read_lines("./test_input.txt") {
    if let Ok(lines) = read_lines("./input.txt") {
        for line in lines.flatten() {
            let nums: Vec<i8> = line
                .split_whitespace()
                .filter_map(|s| s.parse::<i8>().ok())
                .collect();

            let report = Report {
                levels: nums.clone(),
                // apply damper for part 2
                safe: is_safe(&nums, true),
            };

            reports.push(report);
        }
    }

    println!("number of reports: {}", reports.len());

    // sum of safe reports
    let safe_reports = reports.iter().filter(|&r| r.safe).count();
    println!("Safe reports: {}", safe_reports);
}
