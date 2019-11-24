/**
 * triplet_challenge is an application that extracts the top 3 triplet words of a file
 *
 * Copyright (C) 2019 Pablo Marcos Oltra
 *
 * This file is part of triplet_challenge.
 *
 * triplet_challenge is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * triplet_challenge is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with triplet_challenge.  If not, see <http://www.gnu.org/licenses/>.
 */

use std::env;
use std::fs;
use std::collections::HashMap;

#[cfg(test)]
mod test;

fn sanitize(content: &str) -> (String, usize) {
    let mut sanitized = String::with_capacity(content.len());
    let mut number = 0;
    let mut last_taken = true;

    for c in content.chars() {
        if c.is_alphanumeric() {
            if !last_taken {
                sanitized.push(' ');
                number = number + 1;
            }
            sanitized.push(c.to_ascii_lowercase());
            last_taken = true;
        } else {
            last_taken = false;
        }
    }

    if last_taken {
        sanitized.push(' ');
        number = number + 1;
    }

    return (sanitized, number);
}

fn generate_map<'a>(content: &'a str, n_words: usize) -> HashMap<&'a str, usize> {
    let mut map: HashMap<&str, usize> = HashMap::with_capacity(n_words - 2);
    let mut words = 0usize;
    let mut base: [usize; 3] = [0; 3];

    for (i, c) in content.char_indices() {
        if c.is_ascii_whitespace() {
            words = words + 1;
            if words >= 3 {
                let key = &content[base[words % 3]..i];
                let value = *map.entry(key).or_insert(0);
                map.insert(key, value + 1);
                //println!("Key \"{}\" collected with value {}", key, map.get(key).unwrap());
            }
            base[words % 3] = i + 1;
        }
    }

    return map;
}

struct Triplet {
    key: String,
    count: usize
}

impl Triplet {
    fn new() -> Triplet {
        Triplet {key: "".to_string(), count: 0}
    }
}

fn collect_max_triplets<'a>(map: &HashMap<&'a str, usize>) -> Vec<Triplet> {
    let mut triplets = vec!(Triplet::new(), Triplet::new(), Triplet::new());

    for (key, value) in map.iter() {
        if *value > triplets[2].count {
            triplets[2] = Triplet{key: key.to_string(), count: *value};
            if *value > triplets[1].count {
                triplets.swap(2, 1);
                if *value > triplets[0].count {
                    triplets.swap(1, 0);
                }
            }
        }
    }

    return triplets;
}

fn main() {
    let args: Vec<String> = env::args().collect();
    if args.len() < 2 {
        eprintln!("Error: You must give a filename as first argument");
        std::process::exit(1);
    }
    let filename = &args[1];
    let content = fs::read_to_string(&filename).expect(&format!("Error reading file {} as first argument", &filename));
    let (s_content, n_words) = sanitize(&content);
    let map = generate_map(&s_content, n_words);
    let max_triplets = collect_max_triplets(&map);

    for triplet in &max_triplets {
        println!("{} - {}", triplet.key, triplet.count);
    }
}
