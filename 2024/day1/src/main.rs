use std::fs;

fn parse_input(filename: String) -> String {
    let file_contents = fs::read_to_string(filename)
        .expect("Couldn't read file");

    return file_contents;
}

// Part 1
fn find_total_diff(mut left: Vec<i32>, mut right: Vec<i32>) -> i32 {

    left.sort();
    right.sort();

    let total_diff: i32 = left.iter()
        .zip(right.iter())
        .map(|(l, r)| (l - r).abs())
        .sum();

    return total_diff;
}

// Part 2
fn find_similarity_score(left: Vec<i32>, right: Vec<i32>) -> i32 {
    let similarity_score: i32 = left.iter()
        .map(|l| right.iter().filter(|r| l == *r).count() as i32 * l)
        .sum();

    return similarity_score;
}

fn main() {

    let puzzle_input = parse_input("input.txt".to_string());

    let mut left : Vec<i32> = Vec::new();
    let mut right: Vec<i32> = Vec::new();

    let lines = puzzle_input.lines();

    for line in lines {

        let numbers: Vec<&str> = line.split_whitespace().collect();
        left.push(numbers[0].parse::<i32>().unwrap());
        right.push(numbers[1].parse::<i32>().unwrap());

    }

    let total_diff = find_total_diff(left.clone(), right.clone());
    println!("Total diff: {}", total_diff);

    let similarity_score = find_similarity_score(left.clone(), right.clone());
    println!("Similarity score: {}", similarity_score);
}
