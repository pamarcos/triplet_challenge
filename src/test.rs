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
use super::*;

#[test]
fn test_sanitize() {
    let (string, number) = sanitize("THiS   is\n\n\na    t35t");
    assert_eq!(string, "this is a t35t ");
    assert_eq!(number, 4);
}

#[test]
fn test_generate_map() {
    let (content, words) = sanitize("this is a test to see how it goes is a test to see");
    let map = generate_map(&content, words);
    assert_eq!(map.len(), words - 1 - 2 * 2);
    for entry in &map {
        println!("{} : {}", entry.0, entry.1);
    }
    assert_eq!(map.get("this is a"), Some(&1usize));
    assert_eq!(map.get("is a test"), Some(&2usize));
    assert_eq!(map.get("a test to"), Some(&2usize));
    assert_eq!(map.get("test to see"), Some(&2usize));
    assert_eq!(map.get("to see how"), Some(&1usize));
    assert_eq!(map.get("see how it"), Some(&1usize));
    assert_eq!(map.get("how it goes"), Some(&1usize));
    assert_eq!(map.get("it goes is"), Some(&1usize));
    assert_eq!(map.get("goes is a"), Some(&1usize));
}
