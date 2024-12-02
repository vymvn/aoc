use std::fs;

fn main() {

    let mut left : Vec<i32> = Vec::new();
    let mut right : Vec<i32> = Vec::new();

    let puzzle_input = fs::read_to_string("test_input.txt")
        .expect("Couldn't read file");

    let lines = puzzle_input.lines();

    for line in lines {

        let numbers: Vec<&str> = line.split_whitespace().collect();
        left.push(numbers[0].parse::<i32>().unwrap());
        right.push(numbers[1].parse::<i32>().unwrap());

    }

    left.iter()
        .zip(right.iter())
        .for_each(|(l, r)| println!("{} || {}", l, r));

    left.sort();
    right.sort();

    println!("==========================");

    let total_diff: i32 = left.iter()
        .zip(right.iter())
        .map(|(l, r)| (*l - *r).abs())
        .sum();

    println!("Total diff: {}", total_diff);

    let test: Vec<_> = left.iter()
      .filter(|&l| !right.contains(l))
      .collect();

    println!("Test: {:?}", test);
}
