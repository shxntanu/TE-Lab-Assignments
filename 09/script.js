/*
use:

load('script.js');
*/

db = connect("mongodb://localhost/31380_db");

// Creating a movies collection
db.createCollection("movies");

/*
true
*/

// Inserting data into collection
db.movies.insertMany([
    {
        title: "The Shawshank Redemption",
        director: "Frank Darabont",
        releaseYear: 1994,
        genre: ["Drama", "Crime"],
        rating: 9.3,
    },
    {
        title: "The Godfather",
        director: "Francis Ford Coppola",
        releaseYear: 1972,
        genre: ["Crime", "Drama"],
        rating: 9.2,
    },
    {
        title: "Pulp Fiction",
        director: "Quentin Tarantino",
        releaseYear: 1994,
        genre: ["Crime", "Drama"],
        rating: 8.9,
    },
    {
        title: "The Dark Knight",
        director: "Christopher Nolan",
        releaseYear: 2008,
        genre: ["Action", "Crime", "Drama"],
        rating: 9.0,
    },
    {
        title: "Inception",
        director: "Christopher Nolan",
        releaseYear: 2010,
        genre: ["Action", "Adventure", "Sci-Fi"],
        rating: 8.8,
    },
]);

// Selecting all movies
db.movies.find().pretty();

/*
[
  {
    _id: ObjectId("6549072b4f850d45854084bb"),
    title: 'The Shawshank Redemption',
    director: 'Frank Darabont',
    releaseYear: 1994,
    genre: [ 'Drama', 'Crime' ],
    rating: 9.3
  },
  {
    _id: ObjectId("6549072b4f850d45854084bc"),
    title: 'The Godfather',
    director: 'Francis Ford Coppola',
    releaseYear: 1972,
    genre: [ 'Crime', 'Drama' ],
    rating: 9.2
  },
  {
    _id: ObjectId("6549072b4f850d45854084bd"),
    title: 'Pulp Fiction',
    director: 'Quentin Tarantino',
    releaseYear: 1994,
    genre: [ 'Crime', 'Drama' ],
    rating: 8.9
  },
  {
    _id: ObjectId("6549072b4f850d45854084be"),
    title: 'The Dark Knight',
    director: 'Christopher Nolan',
    releaseYear: 2008,
    genre: [ 'Action', 'Crime', 'Drama' ],
    rating: 9
  },
  {
    _id: ObjectId("6549072b4f850d45854084bf"),
    title: 'Inception',
    director: 'Christopher Nolan',
    releaseYear: 2010,
    genre: [ 'Action', 'Adventure', 'Sci-Fi' ],
    rating: 8.8
  }
]
*/

// Finding by name
db.movies.find({ title: "The Godfather" });

/*
[
  {
    _id: ObjectId("6549072b4f850d45854084bc"),
    title: 'The Godfather',
    director: 'Francis Ford Coppola',
    releaseYear: 1972,
    genre: [ 'Crime', 'Drama' ],
    rating: 9.2
  }
]
*/

// Finding by rating
db.movies.find({ rating: { $gt: 9 } });

/*
[
  {
    _id: ObjectId("6549072b4f850d45854084bb"),
    title: 'The Shawshank Redemption',
    director: 'Frank Darabont',
    releaseYear: 1994,
    genre: [ 'Drama', 'Crime' ],
    rating: 9.3
  },
  {
    _id: ObjectId("6549072b4f850d45854084bc"),
    title: 'The Godfather',
    director: 'Francis Ford Coppola',
    releaseYear: 1972,
    genre: [ 'Crime', 'Drama' ],
    rating: 9.2
  }
]
*/

// Updating a document
db.movies.updateOne({ title: "The Godfather" }, { $set: { rating: 9.9 } });

/*
{
  acknowledged: true,
  insertedId: null,
  matchedCount: 1,
  modifiedCount: 1,
  upsertedCount: 0
}
*/

// Deprecated, use updateOne instead
db.movies.save(
    { _id: ObjectId("6549072b4f850d45854084bb") },
    {
        title: "The Shawshank Redemption",
        director: "Frank Darabont",
        releaseYear: 1994,
        genre: ["Drama", "Crime", "Thriller"],
        rating: 9.5,
    }
);

// Deleting a document
db.movies.deleteOne({ title: "The Shawshank Redemption" });

/*
{ acknowledged: true, deletedCount: 1 }
*/

// AND operator
db.movies.find({
    title: "The Dark Knight",
    director: "Christopher Nolan",
});

/*
[
  {
    _id: ObjectId("6549072b4f850d45854084be"),
    title: 'The Dark Knight',
    director: 'Christopher Nolan',
    releaseYear: 2008,
    genre: [ 'Action', 'Crime', 'Drama' ],
    rating: 9
  }
]
*/

// OR operator
db.movies.find({
    $or: [{ director: "Christopher Nolan" }, { genre: "Action" }],
});

/*
[
  {
    _id: ObjectId("6549072b4f850d45854084be"),
    title: 'The Dark Knight',
    director: 'Christopher Nolan',
    releaseYear: 2008,
    genre: [ 'Action', 'Crime', 'Drama' ],
    rating: 9
  },
  {
    _id: ObjectId("6549072b4f850d45854084bf"),
    title: 'Inception',
    director: 'Christopher Nolan',
    releaseYear: 2010,
    genre: [ 'Action', 'Adventure', 'Sci-Fi' ],
    rating: 8.8
  }
]
*/
