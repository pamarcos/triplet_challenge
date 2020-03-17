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
use std::collections::HashMap;
use std::env;
use std::fs;
use std::hash::{BuildHasherDefault, Hasher};
use std::time::Instant;

#[cfg(test)]
mod test;

/// FNV hash taken from https://github.com/servo/rust-fnv
///
/// An implementation of the Fowler–Noll–Vo hash function.
///
/// See the [crate documentation](index.html) for more details.
#[allow(missing_copy_implementations)]
pub struct FnvHasher(u64);

impl Default for FnvHasher {
    #[inline]
    fn default() -> FnvHasher {
        FnvHasher(0xcbf29ce484222325)
    }
}

impl Hasher for FnvHasher {
    #[inline]
    fn finish(&self) -> u64 {
        self.0
    }

    #[inline]
    fn write(&mut self, bytes: &[u8]) {
        let FnvHasher(mut hash) = *self;

        for byte in bytes.iter() {
            hash = hash ^ (*byte as u64);
            hash = hash.wrapping_mul(0x100000001b3);
        }

        *self = FnvHasher(hash);
    }
}

/// A `HashMap` using a default FNV hasher.
type FnvHashMap<K, V> = HashMap<K, V, BuildHasherDefault<FnvHasher>>;

type TripletHashMap<'a> = FnvHashMap<&'a str, usize>;

fn sanitize(content: &str) -> (String, usize) {
    let mut sanitized = String::with_capacity(content.len());
    let mut number = 0;
    let mut last_taken = true;

    for c in content.chars() {
        if c.is_alphanumeric() {
            if !last_taken {
                sanitized.push(' ');
                number += 1;
            }
            sanitized.push(c.to_ascii_lowercase());
            last_taken = true;
        } else {
            last_taken = false;
        }
    }

    if last_taken {
        sanitized.push(' ');
        number += 1;
    }

    return (sanitized, number);
}

fn generate_map<'a>(content: &'a str, n_words: usize) -> TripletHashMap<'a> {
    let mut map: TripletHashMap =
        TripletHashMap::with_capacity_and_hasher(n_words - 2, Default::default());
    let mut words = 0usize;
    let mut base: [usize; 3] = [0; 3];

    for (i, c) in content.char_indices() {
        if c.is_ascii_whitespace() {
            words += 1;
            if words >= 3 {
                let key = &content[base[words % 3]..i];
                map.entry(key).and_modify(|e| *e += 1).or_insert(1);
                //println!("Key \"{}\" collected with value {}", key, map.get(key).unwrap());
            }
            base[words % 3] = i + 1;
        }
    }

    return map;
}

struct Triplet {
    key: String,
    count: usize,
}

impl Triplet {
    fn new() -> Self {
        Self {
            key: "".to_string(),
            count: 0,
        }
    }
}

fn collect_max_triplets(map: &TripletHashMap) -> Vec<Triplet> {
    let mut triplets = vec![Triplet::new(), Triplet::new(), Triplet::new()];

    for (&key, &value) in map.iter() {
        if value > triplets[2].count {
            triplets[2] = Triplet {
                key: key.to_string(),
                count: value,
            };
            if value > triplets[1].count {
                triplets.swap(2, 1);
                if value > triplets[0].count {
                    triplets.swap(1, 0);
                }
            }
        }
    }

    return triplets;
}

fn main() {
    let start = Instant::now();
    let args: Vec<String> = env::args().collect();
    if args.len() < 2 {
        eprintln!("Error: You must give a filename as first argument");
        std::process::exit(1);
    }
    let filename = &args[1];
    let content = fs::read_to_string(&filename).expect(&format!(
        "Error reading file {} as first argument",
        &filename
    ));

    let mut t1 = Instant::now();
    let (s_content, n_words) = sanitize(&content);
    drop(content); // early drop since no longer used
    eprintln!("Sanitize took {} ms", (Instant::now() - t1).as_millis());

    t1 = Instant::now();
    let map = generate_map(&s_content, n_words);
    eprintln!("Generate map took {} ms", (Instant::now() - t1).as_millis());

    t1 = Instant::now();
    let max_triplets = collect_max_triplets(&map);
    eprintln!("Max triplets took {} ms", (Instant::now() - t1).as_millis());

    for triplet in &max_triplets {
        println!("{} - {}", triplet.key, triplet.count);
    }

    eprintln!("Total time elapsed: {} m", (Instant::now() - start).as_millis());
}
