db = connect("mongodb://localhost/31380_db");

db.createCollection("Products");

db.Products.insertMany([
    {
        name: "Laptop",
        category: "Electronics",
        price: 80000,
        attribute: { color: "white", weight: "2pounds" },
        features: ["16GB RAM", "Intel core"],
        reviews: [
            { user: "amit", rating: 9 },
            { user: "sumit", rating: 8 },
        ],
    },
    {
        name: "Smartphone",
        category: "Electronics",
        price: 56000,
        attributes: { color: "blue", weight: "200g" },
        features: ["128GB memory", "Google assistance"],
        reviews: [
            { user: "riya", rating: 7 },
            { user: "rhea", rating: 9 },
        ],
    },
    {
        name: "T-shirt",
        category: "Clothing",
        price: 800,
        attributes: { color: "black", weight: "200g" },
        features: ["100% cotton", "slim fit"],
        reviews: [
            { user: "amit", rating: 9 },
            { user: "sumit", rating: 8 },
        ],
    },
    {
        name: "Jeans",
        category: "Clothing",
        price: 2000,
        attributes: { color: "blue", weight: "300g" },
        features: ["100% cotton", "slim fit"],
        reviews: [
            { user: "riya", rating: 7 },
            { user: "rhea", rating: 9 },
        ],
    },
    {
        name: "Shoes",
        category: "Footwear",
        price: 3000,
        attributes: { color: "black", weight: "500g" },
        features: ["100% leather", "slim fit"],
        reviews: [
            { user: "amit", rating: 9 },
            { user: "sumit", rating: 8 },
        ],
    },
    {
        name: "Sneakers",
        category: "Footwear",
        price: 2000,
        attributes: { color: "white", weight: "300g" },
        features: ["100% leather", "slim fit"],
        reviews: [
            { user: "riya", rating: 7 },
            { user: "rhea", rating: 9 },
        ],
    },
    {
        name: "Headphones",
        category: "Electronics",
        price: 2000,
        attributes: { color: "black", weight: "300g" },
        features: ["100% leather", "slim fit"],
        reviews: [
            { user: "amit", rating: 9 },
            { user: "sumit", rating: 8 },
        ],
    },
    {
        name: "Earphones",
        category: "Electronics",
        price: 2000,
        attributes: { color: "white", weight: "300g" },
        features: ["100% leather", "slim fit"],
        reviews: [
            { user: "riya", rating: 7 },
            { user: "rhea", rating: 9 },
        ],
    },
]);

db.Products.insertOne({
    name: "Bookshelf",
    category: "Furniture",
    price: 25000,
    attributes: { color: "black", weight: "5kgs" },
    features: ["12 small shelves", "2 drawers"],
    reviews: [
        { user: "Ruchi", rating: 10 },
        { user: "Aarti", rating: 8 },
    ],
});

/*
sum category wise
*/

db.Products.aggregate([
    { $group: { _id: "$category", sum: { $sum: "$price" } } },
]);

// Find Products with price less than 25,000
db.Products.aggregate([{ $match: { price: { $lt: 25000 } } }]);

/*to skip the first two documents*/
db.Products.aggregate([{ $skip: 2 }]);

db.Products.aggregate([
    { $group: { _id: "$category", avgprice: { $avg: "$price" } } },
]);

db.Products.aggregate([
    {
        $project: {
            _id: 0,
            name: 1,
            price: 1,
            no_of_reviews: { $size: "$reviews" },
        },
    },
]);

db.Products.aggregate([
    { $group: { _id: "$category", maxPrice: { $max: "$price" } } },
]);

// Index the table on name and price
db.Products.createIndex({ name: 1, price: -1 });

db.Products.find({ name: "Jeans", price: 2000 }).hint("name_1_price_-1");

db.Products.createIndex({ name: 1 });

// --------- ORDERS ---------

db.createCollection("orders");

db.orders.insertMany([
    {
        _id: 0,
        name: "Pepperoni",
        size: "small",
        price: 19,
        quantity: 10,
        date: ISODate("2021-03-13T08:14:30Z"),
    },
    {
        _id: 1,
        name: "Pepperoni",
        size: "medium",
        price: 20,
        quantity: 20,
        date: ISODate("2021-03-13T09:13:24Z"),
    },
    {
        _id: 2,
        name: "Pepperoni",
        size: "large",
        price: 21,
        quantity: 30,
        date: ISODate("2021-03-17T09:22:12Z"),
    },
    {
        _id: 3,
        name: "Cheese",
        size: "small",
        price: 12,
        quantity: 15,
        date: ISODate("2021-03-13T11:21:39.736Z"),
    },
    {
        _id: 4,
        name: "Cheese",
        size: "medium",
        price: 13,
        quantity: 50,
        date: ISODate("2022-01-12T21:23:13.331Z"),
    },
    {
        _id: 5,
        name: "Cheese",
        size: "large",
        price: 14,
        quantity: 10,
        date: ISODate("2022-01-12T05:08:13Z"),
    },
    {
        _id: 6,
        name: "Vegan",
        size: "small",
        price: 17,
        quantity: 10,
        date: ISODate("2021-01-13T05:08:13Z"),
    },
    {
        _id: 7,
        name: "Vegan",
        size: "medium",
        price: 18,
        quantity: 10,
        date: ISODate("2021-01-13T05:10:13Z"),
    },
]);

db.orders.aggregate(
    {
        $match: {
            date: {
                $gte: new ISODate("2020-01-30"),
                $lt: new ISODate("2022-01-30"),
            },
        },
    },
    {
        $group: {
            _id: { $dateToString: { format: "%Y-%m-%d", date: "$date" } },
            totalOrderValue: { $sum: { $multiply: ["$price", "$quantity"] } },
            averageOrderQuantity: { $avg: "$quantity" },
        },
    },
    { $sort: { totalOrderValue: -1 } }
);
