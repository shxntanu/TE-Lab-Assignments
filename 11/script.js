var mapFunction = function () {
    emit(this.category, this.price); // {category: price}
};

var reduceFunction = function (key, values) { // key: category, values: price
    var sum = 0;
    for (var i = 0; i < values.length; i++) {
        sum += values[i];
    }
    return sum / values.length;
};

db.Products.mapReduce(mapFunction, reduceFunction, {
    out: "average_prices",
    query: { category: "Electronics" },
});

// { category: "Electronics", price: [80000, 56000, 2000]]}

db.Products.mapReduce(mapFunction, reduceFucntion, { out: "average_prices" });

/*Generalized to get sum of all the products*/
var mapFunction = function () {
    emit("total", this.price);
};
var reduceFunction = function (key, values)  {
    return Array.sum(values);
};
db.Products.mapReduce(mapFunction, reduceFunction, { out: "sum_prices" });

// -------------------- Example 2 --------------------

db.createCollection("blog_posts");

db.blog_posts.insertMany([
    {
        _id: 1,
        author: "Alice",
        comments: [
            {
                status: "approved",
                text: "Great post!",
            },
            {
                status: "pending",
                text: "I have a question.",
            },
        ],
    },
    {
        _id: 2,
        author: "Bob",
        comments: [
            {
                status: "approved",
                text: "Nice work!",
            },
            {
                status: "approved",
                text: "I agree with your points.",
            },
        ],
    },
    {
        _id: 3,
        author: "Alice",
        comments: [
            {
                status: "rejected",
                text: "This is not correct.",
            },
            {
                status: "approved",
                text: "Thanks for sharing.",
            },
        ],
    },
    {
        _id: 4,
        author: "Alice",
        comments: [
            {
                status: "approved",
                text: "Please write more.",
            },
            {
                status: "pending",
                text: "Can I get a copy of this?",
            },
        ],
    },
]);

var mapFunction = function () {
    this.comments.forEach(function (comment) {
        emit(
            {
                author: this.author,
                status: comment.status,
            },
            1
        );
    });
};

var reduceFunction = function (key, values) {
    return Array.sum(values);
};

db.blog_posts.mapReduce(mapFunction, reduceFunction, {
    out: "comments_by_author_status", // Store the results in a new collection called "comments_by_author_status"
});
